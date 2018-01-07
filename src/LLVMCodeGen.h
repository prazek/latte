#pragma once

#include "ASTVisitor.h"
#include "LatteBaseVisitor.h"
#include "TypeChecker.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"

class LLVMCodeGen : public ASTVisitor<llvm::Value*> {
public:
  LLVMCodeGen(const TypeChecker &typeChecker, llvm::Module &module)
      : typeChecker(typeChecker), context(module.getContext()), builder(context), module(module) {
  }
  llvm::Value *visitConstStringExpr(ConstStringExpr &constStringExpr) override;
  llvm::Value *visitCallExpr(CallExpr &callExpr) override;
  llvm::Value *visitFunctionDef(FunctionDef &functionDef) override;
  llvm::Value *visitClassDef(ClassDef &classDef) override;
  llvm::Value *visitAssignStmt(AssignStmt &assignStmt) override;
  llvm::Value *visitVarExpr(VarExpr &varExpr) override;
  llvm::Value *visitConstIntExpr(ConstIntExpr &constIntExpr) override;
  llvm::Value *visitBooleanExpr(BooleanExpr &booleanExpr) override;
  llvm::Value *visitBinExpr(BinExpr &binExpr) override;
  llvm::Value *visitReturnStmt(ReturnStmt &returnStmt) override;
  llvm::Value *visitIfStmt(IfStmt &condStmt) override;
  llvm::Value *visitWhileStmt(WhileStmt &whileStmt) override;
  llvm::Value *visitDeclStmt(DeclStmt &declStmt) override;
  llvm::Value *visitIncrStmt(IncrStmt &incrStmt) override;
  llvm::Value *visitDecrStmt(DecrStmt &incrStmt) override;
  llvm::Value *visitUnaryExpr(UnaryExpr &unaryExpr) override;

private:
  llvm::Value *visitVarDecl(VarDecl &declItem);
  llvm::Value* handleAnd(BinExpr &andExpr);
  llvm::Value* handleOr(BinExpr &andExpr);
  llvm::Value *defaultInitializer(Type *type);

private:
  llvm::Function *currentFunction = nullptr;
  std::unordered_map<VarDecl*, llvm::Value*> varAddr;
  const TypeChecker &typeChecker;

  llvm::LLVMContext &context;
  llvm::IRBuilder<> builder;
  llvm::Module &module;
  llvm::Value *getString(const std::string& string);
  llvm::Value *getEmptyString();
};




