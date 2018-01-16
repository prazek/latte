

#include "ControlFlowAnalyzer.h"


ReturnInfo ControlFlowAnalyzer::visitFunctionDef(FunctionDef &functionDef) {
  bool isVoidFunc = SimpleType::isVoid(*functionDef.getFunType()->returnType);
  auto returnInfo = visitBlock(functionDef.block);
  if (returnInfo == ReturnInfo::EndsWithoutReturn && !isVoidFunc)
    diagnostics.issueError("Function " + functionDef.name + " ends without return");

  return {};
}

ReturnInfo ControlFlowAnalyzer::visitClassDef(ClassDef &) {
  return ReturnInfo::NoInfo;
}

ReturnInfo ControlFlowAnalyzer::visitDeclStmt(DeclStmt &) {
  return ReturnInfo::NoInfo;
}

ReturnInfo ControlFlowAnalyzer::visitIncrStmt(IncrStmt &) {
  return ReturnInfo::NoInfo;
}

ReturnInfo ControlFlowAnalyzer::visitDecrStmt(DecrStmt &) {
  return ReturnInfo::NoInfo;
}

ReturnInfo ControlFlowAnalyzer::visitReturnStmt(ReturnStmt &) {
  return ReturnInfo::EndsWithReturn;
}

ReturnInfo ControlFlowAnalyzer::visitIfStmt(IfStmt &condStmt) {
  auto exprInfo = visitExpr(*condStmt.condition);
  auto ifInfo = visitStmt(*condStmt.stmt);
  if (exprInfo == ReturnInfo::TrueExpr)
    return ifInfo;

  if (condStmt.elseStmt) {
    auto elseInfo = visitStmt(*condStmt.elseStmt);
    if (exprInfo == ReturnInfo::FalseExpr)
      return elseInfo;

    if (ifInfo == ReturnInfo::EndsWithReturn && elseInfo == ReturnInfo::EndsWithReturn)
      return ReturnInfo::EndsWithReturn;
  }
  return ReturnInfo::NoInfo;
}

ReturnInfo ControlFlowAnalyzer::visitWhileStmt(WhileStmt &) {
  return ReturnInfo::NoInfo;
}

ReturnInfo ControlFlowAnalyzer::visitUnaryExpr(UnaryExpr &) {
  // FIXME: we could handle it also.
  return ReturnInfo::OtherExpr;
}

ReturnInfo ControlFlowAnalyzer::visitBinExpr(BinExpr &binExpr) {
  if (binExpr.binOp != BinExpr::BinOp::Or
      && binExpr.binOp != BinExpr::BinOp::And)
    return ReturnInfo::OtherExpr;

  auto lhsInfo = visitExpr(*binExpr.lhs);
  auto rhsInfo = visitExpr(*binExpr.rhs);
  if (binExpr.binOp == BinExpr::BinOp::Or) {
    if (lhsInfo == ReturnInfo::TrueExpr || rhsInfo == ReturnInfo::TrueExpr)
      return ReturnInfo::TrueExpr;
    if (lhsInfo == ReturnInfo::FalseExpr && rhsInfo == ReturnInfo::FalseExpr)
      return ReturnInfo::FalseExpr;
  } else {
    assert(binExpr.binOp == BinExpr::BinOp::And);
    if (lhsInfo == ReturnInfo::TrueExpr && rhsInfo == ReturnInfo::TrueExpr)
      return ReturnInfo::TrueExpr;
    if (lhsInfo == ReturnInfo::FalseExpr || rhsInfo == ReturnInfo::FalseExpr)
      return ReturnInfo::FalseExpr;
  }
  return ReturnInfo::OtherExpr;
}

ReturnInfo ControlFlowAnalyzer::visitVarExpr(VarExpr &) {
  return ReturnInfo::OtherExpr;
}

ReturnInfo ControlFlowAnalyzer::visitUnreachableStmt(UnreachableStmt &) {
  return ReturnInfo::NoInfo;
}
ReturnInfo ControlFlowAnalyzer::visitConstIntExpr(ConstIntExpr &) {
  return ReturnInfo::OtherExpr;
}

ReturnInfo ControlFlowAnalyzer::visitBooleanExpr(BooleanExpr &booleanExpr) {
  return booleanExpr.value ? ReturnInfo::TrueExpr : ReturnInfo::FalseExpr;
}

ReturnInfo ControlFlowAnalyzer::visitCallExpr(CallExpr &) {
  return ReturnInfo::OtherExpr;
}

ReturnInfo ControlFlowAnalyzer::visitConstStringExpr(ConstStringExpr &) {
  return ReturnInfo::OtherExpr;
}

ReturnInfo ControlFlowAnalyzer::visitBlock(Block &block) {
  for (Stmt* stmt : block.stmts)
    if (visitStmt(*stmt) == ReturnInfo::EndsWithReturn)
      return ReturnInfo::EndsWithReturn;
  
  return ReturnInfo::EndsWithoutReturn;
}
ReturnInfo ControlFlowAnalyzer::visitRValueImplicitCast(RValueImplicitCast &) {
  return ReturnInfo::OtherExpr;
}
ReturnInfo ControlFlowAnalyzer::visitFunExpr(FunExpr &) {
  return ReturnInfo::OtherExpr;
}
ReturnInfo ControlFlowAnalyzer::visitMemberExpr(MemberExpr &) {
  return ReturnInfo::OtherExpr;
}
ReturnInfo ControlFlowAnalyzer::visitNewExpr(NewExpr &newExpr) {
  return ReturnInfo::OtherExpr;
}
ReturnInfo ControlFlowAnalyzer::visitClassCastExpr(ClassCastExpr &classCastExpr) {
  return ReturnInfo::OtherExpr;
}
