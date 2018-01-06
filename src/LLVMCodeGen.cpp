

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
  auto *funType = llvm::cast<llvm::FunctionType>(functionDef.functionType->toLLVMType(module->getContext()));

  llvm::Function *function  =
      llvm::Function::Create(funType,
                             llvm::Function::ExternalLinkage, functionDef.name,
                             module.get());
  currentFunction = function;
  // Check if single scope
  variableScope.openNewScope();
  // TODO visit arguments.
  for (ArgDecl & argDecl : functionDef.arguments) {
    // TODO dodac argumenty

    //variableScope.addVariableType(argDecl.name, );
  }

  currentFunction = function;
  llvm::BasicBlock *bb = llvm::BasicBlock::Create(module->getContext(), "entry", function);
  builder.SetInsertPoint(bb);


  visitBlock(functionDef.block);

  variableScope.closeScope();
  return {};
}

llvm::Value *LLVMCodeGen::visitClassDef(ClassDef &/*classDef*/) {
  return nullptr;
}

llvm::Value *LLVMCodeGen::visitDeclItem(DeclItem &declItem) {

  llvm::Type * Type = declItem.parent->type->toLLVMType(module->getContext());
  auto *instruction = builder.CreateAlloca(Type);
  variableScope.addVariableType(declItem.name, instruction);

  if (declItem.initializer) {
    llvm::Value* value = visitExpr(*declItem.initializer);
    builder.CreateStore(value, instruction);
  }
  return instruction;
}

llvm::Value *LLVMCodeGen::visitAssignStmt(AssignStmt &assignStmt) {
  llvm::Value* rhs = visitExpr(*assignStmt.initializer);

  llvm::Value* var = variableScope.findVariableType(assignStmt.name);
  return builder.CreateStore(rhs, var);
}


llvm::Value *LLVMCodeGen::visitVarExpr(VarExpr &varExpr) {
  auto *value = variableScope.findVariableType(varExpr.name);
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
  auto *trueBlock = llvm::BasicBlock::Create(module->getContext(), "cond.rhs", currentFunction);
  auto *afterBlock = llvm::BasicBlock::Create(module->getContext(), "", currentFunction);

  builder.CreateCondBr(lhsVal, trueBlock, afterBlock);

  builder.SetInsertPoint(trueBlock);
  auto *rhsVal = visitExpr(*andExpr.rhs);
  builder.CreateBr(afterBlock);

  builder.SetInsertPoint(afterBlock);
  llvm::PHINode *phiInstr = builder.CreatePHI(llvm::IntegerType::getInt1Ty(context), 2);
  phiInstr->addIncoming(llvm::ConstantInt::get(llvm::IntegerType::getInt1Ty(context),
                                                 false), bb);

  phiInstr->addIncoming(rhsVal, trueBlock);
  return phiInstr;
}

llvm::Value* LLVMCodeGen::handleOr(BinExpr &orExpr) {
  auto *lhsVal = visitExpr(*orExpr.lhs);
  llvm::BasicBlock* bb = builder.GetInsertBlock();
  auto *falseBlock = llvm::BasicBlock::Create(module->getContext(), "cond.rhs", currentFunction);
  auto *afterBlock = llvm::BasicBlock::Create(module->getContext(), "", currentFunction);

  builder.CreateCondBr(lhsVal, afterBlock, falseBlock);

  builder.SetInsertPoint(falseBlock);
  auto *rhsVal = visitExpr(*orExpr.rhs);
  builder.CreateBr(afterBlock);

  builder.SetInsertPoint(afterBlock);
  llvm::PHINode *phiInstr = builder.CreatePHI(llvm::IntegerType::getInt1Ty(context), 2);
  phiInstr->addIncoming(llvm::ConstantInt::get(llvm::IntegerType::getInt1Ty(context),
                                               true), bb);

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
  }

  llvm_unreachable("Unhandled bin op");
}


llvm::Value *LLVMCodeGen::visitReturnStmt(ReturnStmt &returnStmt) {
  if (returnStmt.expr)
    return builder.CreateRet(visitExpr(*returnStmt.expr));
  return builder.CreateRetVoid();
}
llvm::Value *LLVMCodeGen::visitIfStmt(IfStmt &condStmt) {

  llvm::BasicBlock *labTrue = llvm::BasicBlock::Create(module->getContext(), "if", currentFunction);
  std::string nextBlockName = condStmt.elseStmt == nullptr ? "" : "else";
  llvm::BasicBlock *labFalse = llvm::BasicBlock::Create(module->getContext(), nextBlockName, currentFunction);

  llvm::Value *cmp = visitExpr(*condStmt.condition);
  builder.CreateCondBr(cmp, labTrue, labFalse);
  builder.SetInsertPoint(labTrue);
  visitStmt(*condStmt.stmt);
  llvm::BasicBlock *labAfter = labFalse;

  if (condStmt.elseStmt) {
    labAfter =
        llvm::BasicBlock::Create(module->getContext(), "", currentFunction);

    builder.CreateBr(labAfter);
    builder.SetInsertPoint(labFalse);
    visitStmt(*condStmt.elseStmt);
  }
  builder.CreateBr(labAfter);
  builder.SetInsertPoint(labAfter);
  return nullptr;
}

llvm::Value *LLVMCodeGen::visitWhileStmt(WhileStmt &whileStmt) {

  llvm::BasicBlock *condBlock = llvm::BasicBlock::Create(module->getContext(), "loop.cond", currentFunction);
  llvm::BasicBlock *loopBlock = llvm::BasicBlock::Create(module->getContext(), "loop", currentFunction);
  llvm::BasicBlock *after = llvm::BasicBlock::Create(module->getContext(), "", currentFunction);

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
