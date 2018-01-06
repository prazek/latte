#pragma once

#include "ASTVisitor.h"
#include "LatteBaseVisitor.h"
#include "TypeChecker.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"

class LLVMCodeGen : public ASTVisitor<llvm::Value*> {
public:
  LLVMCodeGen(const TypeChecker &typeChecker)
  // TODO file
      : typeChecker(typeChecker), builder(context), module(std::make_unique<llvm::Module>("file", context)){
  }

  llvm::Value *visitFunctionDef(FunctionDef &functionDef) override;
  llvm::Value *visitClassDef(ClassDef &classDef) override;
  llvm::Value *visitDeclItem(DeclItem &declItem) override;
  llvm::Value *visitAssignStmt(AssignStmt &assignStmt) override;
  llvm::Value *visitVarExpr(VarExpr &varExpr) override;
  llvm::Value *visitConstIntExpr(ConstIntExpr &constIntExpr) override;
  llvm::Value *visitBooleanExpr(BooleanExpr &booleanExpr) override;
  llvm::Value *visitBinExpr(BinExpr &binExpr) override;
  llvm::Value *visitReturnStmt(ReturnStmt &returnStmt) override;
  llvm::Value *visitIfStmt(IfStmt &condStmt) override;
  llvm::Value *visitWhileStmt(WhileStmt &whileStmt) override;

private:
  llvm::Value* handleAnd(BinExpr &andExpr);
  llvm::Value* handleOr(BinExpr &andExpr);


private:
  llvm::Function *currentFunction = nullptr;
  VariableScope<llvm::Value*> variableScope;


  const TypeChecker &typeChecker;
public:
  llvm::LLVMContext context;
  llvm::IRBuilder<> builder;
  std::unique_ptr<llvm::Module> module;
};




