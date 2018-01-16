#pragma once
#include "ASTVisitor.h"
#include "Diagnostic.h"

enum class ReturnInfo {
  TrueExpr,
  FalseExpr,
  OtherExpr,
  
  EndsWithoutReturn,
  EndsWithReturn,
  NoInfo
};

class ControlFlowAnalyzer : public ASTVisitor<ReturnInfo> {
public:
  ControlFlowAnalyzer(Diagnostic &diagnostic) : diagnostics(diagnostic) {}

  ReturnInfo visitFunctionDef(FunctionDef &functionDef) override;
  ReturnInfo visitClassDef(ClassDef &classDef) override;
  ReturnInfo visitDeclStmt(DeclStmt &declStmt) override;
  ReturnInfo visitIncrStmt(IncrStmt &incrStmt) override;
  ReturnInfo visitDecrStmt(DecrStmt &incrStmt) override;
  ReturnInfo visitReturnStmt(ReturnStmt &returnStmt) override;
  ReturnInfo visitIfStmt(IfStmt &condStmt) override;
  ReturnInfo visitWhileStmt(WhileStmt &whileStmt) override;
  ReturnInfo visitUnaryExpr(UnaryExpr &unaryExpr) override;
  ReturnInfo visitBinExpr(BinExpr &binExpr) override;
  ReturnInfo visitVarExpr(VarExpr &varExpr) override;
  ReturnInfo visitUnreachableStmt(UnreachableStmt &unreachableStmt) override;
  ReturnInfo visitConstIntExpr(ConstIntExpr &constIntExpr) override;
  ReturnInfo visitBooleanExpr(BooleanExpr &ReturnInfoeanExpr) override;
  ReturnInfo visitCallExpr(CallExpr &callExpr) override;
  ReturnInfo visitConstStringExpr(ConstStringExpr &constStringExpr) override;
  ReturnInfo visitBlock(Block &block) override;
  ReturnInfo visitRValueImplicitCast(RValueImplicitCast &implicitCast) override;
  ReturnInfo visitFunExpr(FunExpr &funExpr) override;
  ReturnInfo visitMemberExpr(MemberExpr &memberExpr) override;

private:
  bool isVoidFunc;
  Diagnostic& diagnostics;
};




