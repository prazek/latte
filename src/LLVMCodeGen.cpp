

#include "LLVMCodeGen.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"

#include "llvm/IR/Verifier.h"
#include "BuiltinFunctions.h"
#include "LLVMClassCodeGen.h"

llvm::Value *LLVMCodeGen::visitFunctionDef(FunctionDef &functionDef) {
  varAddr.clear();
  llvm::Function *function = module.getFunction(functionDef.name);
  currentFunction = function;

  llvm::BasicBlock *bb = llvm::BasicBlock::Create(module.getContext(), "entry", function);
  builder.SetInsertPoint(bb);

  int i = 0;
  for (auto &arg : function->args()) {
    auto *varDecl = functionDef.arguments.at(i++);

    auto *alloca = builder.CreateAlloca(varDecl->type->toLLVMType(module));
    builder.CreateStore(arg.stripPointerCasts(), alloca);
    assert(varAddr.count(varDecl) == 0);
    varAddr[varDecl] = alloca;
  }

  currentFunction = function;
  visitBlock(functionDef.block);
  return nullptr;
}

llvm::Value *LLVMCodeGen::visitClassDef(ClassDef &classDef) {
  for (auto *methodDef : classDef.methodDecls) {
    visitFunctionDef(*methodDef);
  }
  return nullptr;
}


llvm::Value *LLVMCodeGen::visitVarDecl(VarDecl &declItem) {
  auto * rollbackBlock = builder.GetInsertBlock();
  builder.SetInsertPoint(&currentFunction->getEntryBlock(),
                         currentFunction->getEntryBlock().getFirstInsertionPt());
  llvm::Type * Type = declItem.type->toLLVMType(module);
  auto *instruction = builder.CreateAlloca(Type);

  builder.SetInsertPoint(rollbackBlock);
  llvm::Value* value = visitExpr(*declItem.initializer);
  builder.CreateStore(value, instruction);

  assert(varAddr.count(&declItem) == 0);
  varAddr[&declItem] = instruction;
  return instruction;
}

llvm::Value *LLVMCodeGen::visitAssignStmt(AssignStmt &assignStmt) {
  llvm::Value* rhs = visitExpr(*assignStmt.initializer);

  llvm::Value *addr = visitExpr(*assignStmt.lhs);

  return builder.CreateStore(rhs, addr);
}

llvm::Value *LLVMCodeGen::visitRValueImplicitCast(RValueImplicitCast &implicitCast) {
  llvm::Value * addr = visitExpr(*implicitCast.expr);
  return builder.CreateLoad(addr);
}

llvm::Value *LLVMCodeGen::visitVarExpr(VarExpr &varExpr) {
  return varAddr.at(varExpr.decl);
}

llvm::Value *LLVMCodeGen::visitFunExpr(FunExpr &funExpr) {
  return module.getFunction(funExpr.def->name);
}

llvm::Value *LLVMCodeGen::visitConstIntExpr(ConstIntExpr &constIntExpr) {

  return (llvm::Value*)llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(module.getContext()),
                                              constIntExpr.value);
}

llvm::Value *LLVMCodeGen::visitBooleanExpr(BooleanExpr &booleanExpr) {
  return llvm::ConstantInt::get(llvm::IntegerType::getInt1Ty(module.getContext()),
                                booleanExpr.value);
}

llvm::Value* LLVMCodeGen::handleAnd(BinExpr &andExpr) {
  auto *lhsVal = visitExpr(*andExpr.lhs);
  llvm::BasicBlock* bb = builder.GetInsertBlock();
  auto *trueBlock = llvm::BasicBlock::Create(module.getContext(), "cond.rhs", currentFunction);


  builder.SetInsertPoint(trueBlock);
  auto *rhsVal = visitExpr(*andExpr.rhs);
  auto *blockFalse = builder.GetInsertBlock();
  auto *afterBlock = llvm::BasicBlock::Create(module.getContext(), "", currentFunction);

  builder.CreateBr(afterBlock);

  builder.SetInsertPoint(bb);
  builder.CreateCondBr(lhsVal, trueBlock, afterBlock);


  builder.SetInsertPoint(afterBlock);
  llvm::PHINode *phiInstr = builder.CreatePHI(llvm::IntegerType::getInt1Ty(module.getContext()), 2);
  phiInstr->addIncoming(llvm::ConstantInt::getFalse(llvm::IntegerType::getInt1Ty(module.getContext())), bb);

  phiInstr->addIncoming(rhsVal, blockFalse);
  return phiInstr;
}

llvm::Value* LLVMCodeGen::handleOr(BinExpr &orExpr) {
  auto *lhsVal = visitExpr(*orExpr.lhs);
  llvm::BasicBlock* bb = builder.GetInsertBlock();
  auto *falseBlock = llvm::BasicBlock::Create(module.getContext(), "cond.rhs", currentFunction);
  auto *afterBlock = llvm::BasicBlock::Create(module.getContext(), "", currentFunction);
  builder.CreateCondBr(lhsVal, afterBlock, falseBlock);

  builder.SetInsertPoint(falseBlock);
  auto *rhsVal = visitExpr(*orExpr.rhs);
  auto *trueBlock = builder.GetInsertBlock();
  builder.CreateBr(afterBlock);

  builder.SetInsertPoint(afterBlock);
  llvm::PHINode *phiInstr = builder.CreatePHI(llvm::IntegerType::getInt1Ty(module.getContext()), 2);
  phiInstr->addIncoming(llvm::ConstantInt::getTrue(llvm::IntegerType::getInt1Ty(module.getContext())), bb);

  phiInstr->addIncoming(rhsVal, trueBlock);
  return phiInstr;
}

llvm::Value *LLVMCodeGen::handleAdd(BinExpr &binExpr, llvm::Value *lhs, llvm::Value *rhs) {
  if (SimpleType::isIntegral(*binExpr.type))
    return builder.CreateAdd(lhs, rhs);

  llvm::Function *fun = module.getFunction(BuiltinFunctions::StringConcat);
  llvm::SmallVector<llvm::Value*, 2> args;
  args.push_back(lhs);
  args.push_back(rhs);

  return builder.CreateCall(fun, args);
}

llvm::Value *LLVMCodeGen::visitBinExpr(BinExpr &binExpr) {
  switch(binExpr.binOp) {
    case BinExpr::BinOp::And:
      return handleAnd(binExpr);
    case BinExpr::BinOp::Or:
      return handleOr(binExpr);
  default:
    break;
  }

  llvm::Value *lhs = visitExpr(*binExpr.lhs);
  llvm::Value *rhs = visitExpr(*binExpr.rhs);

  switch (binExpr.binOp) {
  case BinExpr::BinOp::LESS:
    return builder.CreateICmpSLT(lhs, rhs);
  case BinExpr::BinOp::LESS_EQ:
    return builder.CreateICmpSLE(lhs, rhs);
  case BinExpr::BinOp::GREATER:
    return builder.CreateICmpSGT(lhs, rhs);
  case BinExpr::BinOp::GREATER_EQ:
    return builder.CreateICmpSGE(lhs, rhs);
  case BinExpr::BinOp::EQUALS:
    return builder.CreateICmpEQ(lhs, rhs);
  case BinExpr::BinOp::NOT_EQUALS:
    return builder.CreateICmpNE(lhs, rhs);
  case BinExpr::BinOp::Mul:
    return builder.CreateMul(lhs, rhs);
  case BinExpr::BinOp::Div:
    return builder.CreateSDiv(lhs, rhs);
  case BinExpr::BinOp::Mod:
    return builder.CreateSRem(lhs, rhs);
  case BinExpr::BinOp::Add:
    return handleAdd(binExpr, lhs, rhs);
  case BinExpr::BinOp::Minus:
    return builder.CreateSub(lhs, rhs);
  case BinExpr::BinOp::And:
  case BinExpr::BinOp::Or:
    break;
  }

  llvm_unreachable("Unhandled bin op");
}

llvm::Value *LLVMCodeGen::visitReturnStmt(ReturnStmt &returnStmt) {
  if (returnStmt.expr)
    return builder.CreateRet(visitExpr(*returnStmt.expr));
  return builder.CreateRetVoid();
}

llvm::Value *LLVMCodeGen::visitUnreachableStmt(UnreachableStmt &) {
  return builder.CreateUnreachable();
}


llvm::Value *LLVMCodeGen::visitIfStmt(IfStmt &condStmt) {


  llvm::Value *cmp = visitExpr(*condStmt.condition);
  llvm::BasicBlock *labTrue = llvm::BasicBlock::Create(module.getContext(), "if", currentFunction);
  std::string nextBlockName = condStmt.elseStmt == nullptr ? "" : "else";
  llvm::BasicBlock *labFalse = llvm::BasicBlock::Create(module.getContext(), nextBlockName, currentFunction);
  builder.CreateCondBr(cmp, labTrue, labFalse);


  llvm::BasicBlock *lastBlock = labTrue;
  builder.SetInsertPoint(labTrue);
  visitStmt(*condStmt.stmt);
  llvm::BasicBlock *labAfter = labFalse;

  if (condStmt.elseStmt) {
    labAfter =
        llvm::BasicBlock::Create(module.getContext(), "", currentFunction);

    if (lastBlock->empty() || !llvm::isa<llvm::TerminatorInst>(lastBlock->back()))
      builder.CreateBr(labAfter);
    builder.SetInsertPoint(labFalse);
    visitStmt(*condStmt.elseStmt);
    lastBlock = labFalse;
  }

  if (lastBlock->empty() || !llvm::isa<llvm::TerminatorInst>(lastBlock->back()))
    builder.CreateBr(labAfter);
  builder.SetInsertPoint(labAfter);
  return nullptr;
}

llvm::Value *LLVMCodeGen::visitWhileStmt(WhileStmt &whileStmt) {

  llvm::BasicBlock *condBlock = llvm::BasicBlock::Create(module.getContext(), "loop.cond", currentFunction);
  llvm::BasicBlock *loopBlock = llvm::BasicBlock::Create(module.getContext(), "loop", currentFunction);
  llvm::BasicBlock *after = llvm::BasicBlock::Create(module.getContext(), "", currentFunction);

  builder.CreateBr(condBlock);

  builder.SetInsertPoint(condBlock);
  llvm::Value *cond = visitExpr(*whileStmt.condition);
  builder.CreateCondBr(cond, loopBlock, after);

  builder.SetInsertPoint(loopBlock);
  visitStmt(*whileStmt.stmt);
  builder.CreateBr(condBlock);

  builder.SetInsertPoint(after);
  return nullptr;
}

llvm::Value *LLVMCodeGen::visitDeclStmt(DeclStmt &declStmt) {
  for (VarDecl *varDecl : declStmt.decls)
    visitVarDecl(*varDecl);
  return {};
}

llvm::Value *LLVMCodeGen::visitCallExpr(CallExpr &callExpr) {
  auto *fun = llvm::cast<llvm::Function>(visitExpr(*callExpr.callee));
  llvm::SmallVector<llvm::Value*, 4> args;
  for (Expr* arg : callExpr.arguments)
    args.push_back(visitExpr(*arg));

  return builder.CreateCall(fun, args);
}

llvm::Value *LLVMCodeGen::visitIncrStmt(IncrStmt &incrStmt) {
  auto *addr = visitExpr(*incrStmt.lhs);
  auto *val = builder.CreateLoad(addr);
  auto *newVal = builder.CreateAdd(
      val, llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(module.getContext()), 1));
  return builder.CreateStore(newVal, addr);
}

llvm::Value *LLVMCodeGen::visitDecrStmt(DecrStmt &incrStmt) {
  auto *addr = visitExpr(*incrStmt.expr);
  auto *val = builder.CreateLoad(addr);
  auto *newVal = builder.CreateSub(
      val, llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(module.getContext()), 1));
  return builder.CreateStore(newVal, addr);

}

llvm::Value *LLVMCodeGen::visitUnaryExpr(UnaryExpr &unaryExpr) {
  llvm::Value *value = visitExpr(*unaryExpr.expr);
  switch (unaryExpr.unOp) {
  case UnaryExpr::UnOp::Minus:
    return builder.CreateSub(llvm::ConstantInt::get(
        llvm::IntegerType::getInt32Ty(module.getContext()), 0), value);
  case UnaryExpr::UnOp::Neg:
    return builder.CreateXor(value, llvm::ConstantInt::getTrue(
        llvm::IntegerType::getInt1Ty(module.getContext())));
  }
  llvm_unreachable("Unhandled unary op");
}

llvm::Value *LLVMCodeGen::visitConstStringExpr(ConstStringExpr &constStringExpr) {
  return getString(constStringExpr.string);
}

llvm::Value *LLVMCodeGen::getString(const std::string &string) {
  llvm::Type *type = llvm::ArrayType::get(llvm::Type::getInt8Ty(module.getContext()),
                                          string.length() + 1);
  llvm::Constant *initializer = llvm::ConstantDataArray::getString(module.getContext(), string, true);
  llvm::SmallVector<llvm::Value*, 2> const_ptr_5_indices;
  llvm::ConstantInt* const_int64_6 =
      llvm::ConstantInt::get(module.getContext(), llvm::APInt(64, llvm::StringRef("0"), 10));
  const_ptr_5_indices.push_back(const_int64_6);
  const_ptr_5_indices.push_back(const_int64_6);

  auto *global = new llvm::GlobalVariable(module,
                                          type, true, llvm::GlobalValue::PrivateLinkage, initializer);

  auto* const_ptr_5 = builder.CreateGEP(global, const_ptr_5_indices);
  return const_ptr_5;
}

llvm::Value *LLVMCodeGen::getEmptyString() {
  static auto *strVal = getString("");
  return strVal;
}

llvm::Value *LLVMCodeGen::visitMemberExpr(MemberExpr &memberExpr) {
  llvm::Value *thisPtr = visitExpr(*memberExpr.thisPtr);

  llvm::ArrayRef<llvm::Value*> indices = {
      llvm::ConstantInt::getSigned(
          llvm::IntegerType::getInt32Ty(module.getContext()), 0),
      llvm::ConstantInt::getSigned(
          llvm::IntegerType::getInt32Ty(module.getContext()),
                                        memberExpr.fieldDecl->fieldId)
  };

  auto *gep = builder.CreateGEP(thisPtr, indices);

  return builder.CreateBitCast(gep, memberExpr.fieldDecl->type->toLLVMType(module)->getPointerTo(0));
}
llvm::Value *LLVMCodeGen::visitNewExpr(NewExpr &newExpr) {
  auto *fun = module.getFunction(getNewOperatorName(newExpr.getClassType()->name));
  return builder.CreateCall(fun);
}
llvm::Value *LLVMCodeGen::visitClassCastExpr(ClassCastExpr &classCastExpr) {
  auto *castedValue = visitExpr(*classCastExpr.casted);
  // TODO casting not null?
  return builder.CreateBitCast(castedValue, classCastExpr.type->toLLVMType(module));
}
llvm::Value *LLVMCodeGen::visitNullExpr(NullExpr &) {
  return llvm::ConstantPointerNull::get(llvm::IntegerType::getInt8PtrTy(module.getContext()));
}
llvm::Value *LLVMCodeGen::visitMemberCallExpr(MemberCallExpr &memberCallExpr) {

  llvm::Value* thisPtr = visitExpr(*memberCallExpr.thisPtr);
  llvm::SmallVector<llvm::Value*, 4> args;
  args.reserve(memberCallExpr.arguments.size() + 1);
  args.push_back(thisPtr);
  for (Expr *arg : memberCallExpr.arguments) {
    args.push_back(visitExpr(*arg));
  }

  llvm::Value *callee = visitExpr(*memberCallExpr.callee);
  return builder.CreateCall(callee, args);
}

llvm::Value *LLVMCodeGen::visitVTableExpr(VTableExpr &vTableExpr) {
  auto *vtableType = llvm::ArrayType::get(llvm::Type::getInt8Ty(module.getContext())->getPointerTo(),
                                          vTableExpr.classDef->methodDecls.size());

  llvm::SmallVector<llvm::Constant*, 4> methods;
  for (FunctionDef *def  : vTableExpr.classDef->methodDecls) {
    auto *vfun = module.getFunction(def->name);
    methods.push_back(llvm::ConstantExpr::getBitCast(vfun, llvm::IntegerType::getInt8PtrTy(module.getContext())));
  }

  auto *initializer = llvm::ConstantArray::get(vtableType, methods);
  auto *vtable = new llvm::GlobalVariable(module, vtableType, true,
                                          llvm::GlobalValue::PrivateLinkage, initializer,
                                          vTableExpr.classDef->className + "$vtable");

  return builder.CreateBitCast(vtable,
                               llvm::PointerType::getInt8PtrTy(module.getContext())->getPointerTo());

}
llvm::Value *LLVMCodeGen::visitMethodExpr(MethodExpr &methodExpr) {
  auto *thisPtr = visitExpr(*methodExpr.thisPtr);

  llvm::ArrayRef<llvm::Value*> vptrIndices = {
      llvm::ConstantInt::getSigned(
          llvm::IntegerType::getInt32Ty(module.getContext()), 0),
      llvm::ConstantInt::getSigned(
          llvm::IntegerType::getInt32Ty(module.getContext()),
          0)
  };

  auto *gep = builder.CreateGEP(thisPtr, vptrIndices);
  auto *vtable = builder.CreateLoad(gep, "vtable");
  vtable->setMetadata(llvm::LLVMContext::MD_invariant_group,
                      llvm::MDNode::get(module.getContext(), llvm::ArrayRef<llvm::Metadata *>()));

  llvm::ArrayRef<llvm::Value*> vtableIndices = {
      llvm::ConstantInt::getSigned(
          llvm::IntegerType::getInt64Ty(module.getContext()),
          methodExpr.funDef->methodID)
  };

  auto *gepVtable = builder.CreateGEP(vtable, vtableIndices);
  auto newType = *cast<FunctionType>(methodExpr.funDef->type);
  newType.argumentTypes.at(0) = methodExpr.thisPtr->type;

  auto *funType = llvm::cast<llvm::FunctionType>(newType.toLLVMType(module));
  auto *vfun = builder.CreateLoad(gepVtable, "vfun");
  vfun->setMetadata(llvm::LLVMContext::MD_invariant_load,
                    llvm::MDNode::get(module.getContext(), llvm::ArrayRef<llvm::Metadata *>()));


  return builder.CreateBitCast(vfun, funType->getPointerTo());
}



