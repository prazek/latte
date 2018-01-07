#pragma once

#include "ASTVisitor.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"


class LLVMCodeGenPrepare : public ASTVisitor<void> {
public:
  LLVMCodeGenPrepare(llvm::Module &module)
      : module(module), builder(module.getContext()) {}

  void visitFunctionDef(FunctionDef &functionDef) override;
  void visitClassDef(ClassDef &classDef) override;
  void visitDeclStmt(DeclStmt &declStmt) override;
  void visitIncrStmt(IncrStmt &incrStmt) override;
  void visitDecrStmt(DecrStmt &incrStmt) override;
  void visitReturnStmt(ReturnStmt &returnStmt) override;
  void visitIfStmt(IfStmt &condStmt) override;
  void visitWhileStmt(WhileStmt &whileStmt) override;
  void visitUnaryExpr(UnaryExpr &unaryExpr) override;
  void visitBinExpr(BinExpr &binExpr) override;
  void visitVarExpr(VarExpr &varExpr) override;
  void visitConstIntExpr(ConstIntExpr &constIntExpr) override;
  void visitBooleanExpr(BooleanExpr &booleanExpr) override;
  void visitCallExpr(CallExpr &callExpr) override;
  void visitConstStringExpr(ConstStringExpr &constStringExpr) override;

private:
  llvm::Module &module;
  llvm::IRBuilder<> builder;
};




