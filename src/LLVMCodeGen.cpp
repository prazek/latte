

#include "LLVMCodeGen.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include "llvm/IR/Verifier.h"


llvm::Value *LLVMCodeGen::visitFunctionDef(FunctionDef &functionDef) {

  llvm::Function *function = module.getFunction(functionDef.name);
  currentFunction = function;

  llvm::BasicBlock *bb = llvm::BasicBlock::Create(context, "entry", function);
  builder.SetInsertPoint(bb);

  int i = 0;
  for (auto &arg : function->args()) {
    auto *varDecl = functionDef.arguments.at(i++);

    auto *alloca = builder.CreateAlloca(varDecl->type->toLLVMType(context));
    // LOL
    auto *stored = builder.CreateStore(alloca, arg.stripPointerCasts());
    varAddr[varDecl] = stored;
  }


  currentFunction = function;
  visitBlock(functionDef.block);

  return {};
}

llvm::Value *LLVMCodeGen::visitClassDef(ClassDef &/*classDef*/) {
  return nullptr;
}

llvm::Value *LLVMCodeGen::defaultInitializer(Type *type) {
  if (auto *simpleType = dyn_cast<SimpleType>(type)) {
    if (simpleType->isBool())
      return llvm::ConstantInt::getFalse(llvm::IntegerType::getInt1Ty(context));
    if (simpleType->isInt())
      return llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(context), 0);
    if (simpleType->isString())
      return getEmptyString();
    llvm_unreachable("No other initializers for simple types");
  }
  llvm_unreachable("Unhandled type");
}

llvm::Value *LLVMCodeGen::visitVarDecl(VarDecl &declItem) {

  llvm::Type * Type = declItem.type->toLLVMType(module.getContext());
  auto *instruction = builder.CreateAlloca(Type);

  auto getInitializer = [&](VarDecl &declItem) {
    if (declItem.initializer)
      return visitExpr(*declItem.initializer);
    return defaultInitializer(declItem.type);
  };

  llvm::Value* value = getInitializer(declItem);
  builder.CreateStore(value, instruction);

  varAddr[&declItem] = instruction;
  return instruction;
}

llvm::Value *LLVMCodeGen::visitAssignStmt(AssignStmt &assignStmt) {
  llvm::Value* rhs = visitExpr(*assignStmt.initializer);

  llvm::Value* var = varAddr.at(assignStmt.decl);
  return builder.CreateStore(rhs, var);
}


llvm::Value *LLVMCodeGen::visitVarExpr(VarExpr &varExpr) {
  auto *value = varAddr.at(varExpr.decl);
  return builder.CreateLoad(value);
}
llvm::Value *LLVMCodeGen::visitConstIntExpr(ConstIntExpr &constIntExpr) {

  return (llvm::Value*)llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(context),
                                              constIntExpr.value);
}
llvm::Value *LLVMCodeGen::visitBooleanExpr(BooleanExpr &booleanExpr) {
  return llvm::ConstantInt::get(llvm::IntegerType::getInt1Ty(context),
                                booleanExpr.value);
}

llvm::Value* LLVMCodeGen::handleAnd(BinExpr &andExpr) {
  auto *lhsVal = visitExpr(*andExpr.lhs);
  llvm::BasicBlock* bb = builder.GetInsertBlock();
  auto *trueBlock = llvm::BasicBlock::Create(module.getContext(), "cond.rhs", currentFunction);
  auto *afterBlock = llvm::BasicBlock::Create(module.getContext(), "", currentFunction);

  builder.CreateCondBr(lhsVal, trueBlock, afterBlock);

  builder.SetInsertPoint(trueBlock);
  auto *rhsVal = visitExpr(*andExpr.rhs);
  builder.CreateBr(afterBlock);

  builder.SetInsertPoint(afterBlock);
  llvm::PHINode *phiInstr = builder.CreatePHI(llvm::IntegerType::getInt1Ty(context), 2);
  phiInstr->addIncoming(llvm::ConstantInt::getFalse(llvm::IntegerType::getInt1Ty(context)), bb);

  phiInstr->addIncoming(rhsVal, trueBlock);
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
  builder.CreateBr(afterBlock);

  builder.SetInsertPoint(afterBlock);
  llvm::PHINode *phiInstr = builder.CreatePHI(llvm::IntegerType::getInt1Ty(context), 2);
  phiInstr->addIncoming(llvm::ConstantInt::getTrue(llvm::IntegerType::getInt1Ty(context)), bb);

  phiInstr->addIncoming(rhsVal, falseBlock);
  return phiInstr;
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
    return builder.CreateAdd(lhs, rhs);
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
llvm::Value *LLVMCodeGen::visitIfStmt(IfStmt &condStmt) {

  llvm::BasicBlock *labTrue = llvm::BasicBlock::Create(module.getContext(), "if", currentFunction);
  std::string nextBlockName = condStmt.elseStmt == nullptr ? "" : "else";
  llvm::BasicBlock *labFalse = llvm::BasicBlock::Create(module.getContext(), nextBlockName, currentFunction);

  llvm::Value *cmp = visitExpr(*condStmt.condition);
  builder.CreateCondBr(cmp, labTrue, labFalse);
  builder.SetInsertPoint(labTrue);
  visitStmt(*condStmt.stmt);
  llvm::BasicBlock *labAfter = labFalse;

  if (condStmt.elseStmt) {
    labAfter =
        llvm::BasicBlock::Create(module.getContext(), "", currentFunction);

    builder.CreateBr(labAfter);
    builder.SetInsertPoint(labFalse);
    visitStmt(*condStmt.elseStmt);
  }
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
  llvm::Function *fun = module.getFunction(callExpr.callee->name);


  llvm::SmallVector<llvm::Value*, 4> args;
  for (Expr* arg : callExpr.arguments)
    args.push_back(visitExpr(*arg));


  return builder.CreateCall(fun, args);
}

llvm::Value *LLVMCodeGen::visitIncrStmt(IncrStmt &incrStmt) {
  auto *addr = varAddr[incrStmt.varDecl];
  auto *val = builder.CreateLoad(addr);
  auto *newVal = builder.CreateAdd(
      val, llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(context), 1));
  return builder.CreateStore(addr, newVal);
}

llvm::Value *LLVMCodeGen::visitDecrStmt(DecrStmt &incrStmt) {
  auto *addr = varAddr[incrStmt.varDecl];
  auto *val = builder.CreateLoad(addr);
  auto *newVal = builder.CreateSub(
      val, llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(context), 1));
  return builder.CreateStore(addr, newVal);

}

llvm::Value *LLVMCodeGen::visitUnaryExpr(UnaryExpr &unaryExpr) {
  llvm::Value *value = visitExpr(*unaryExpr.expr);
  switch (unaryExpr.unOp) {
  case UnaryExpr::UnOp::Minus:
    return builder.CreateSub(llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(context), 0), value);
  case UnaryExpr::UnOp::Neg:
    return builder.CreateXor(value, llvm::ConstantInt::getTrue(llvm::IntegerType::getInt1Ty(context)));
  }
  llvm_unreachable("Unhandled unary op");
}
llvm::Value *LLVMCodeGen::visitConstStringExpr(ConstStringExpr &constStringExpr) {

  return getString(constStringExpr.string);

}

llvm::Value *LLVMCodeGen::getString(const std::string &string) {
  llvm::Type *type = llvm::ArrayType::get(llvm::Type::getInt8Ty(context),
                                          string.length());
  llvm::Constant *initializer = llvm::ConstantDataArray::getString(context, string, true);
  llvm::SmallVector<llvm::Value*, 2> const_ptr_5_indices;
  llvm::ConstantInt* const_int64_6 = llvm::ConstantInt::get(context, llvm::APInt(64, llvm::StringRef("0"), 10));
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
