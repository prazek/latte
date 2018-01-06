

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

llvm::Value *LLVMCodeGen::visitClassDef(ClassDef &classDef) {
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

llvm::Value *LLVMCodeGen::visitMulExpr(MulExpr &mulExpr) {
  llvm::Value *lhs = visitExpr(*mulExpr.lhs);
  llvm::Value *rhs = visitExpr(*mulExpr.rhs);
  return builder.CreateAdd(lhs, rhs);
}

llvm::Value *LLVMCodeGen::visitAddExpr(AddExpr &addExpr) {
  llvm::Value *lhs = visitExpr(*addExpr.lhs);
  llvm::Value *rhs = visitExpr(*addExpr.rhs);
  return builder.CreateAdd(lhs, rhs);
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
