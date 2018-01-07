#pragma once

#include "AST.h"


template <typename T>
class ASTVisitor {

public:
  virtual T visitAST(AST& ast) {
    for (Def *def : ast.definitions)
      visitDef(*def);
    return T();
  }

  virtual T visitDef(Def &def) {
    if (auto *funDef = dyn_cast<FunctionDef>(def))
      return visitFunctionDef(*funDef);
    if (auto *classDef = dyn_cast<ClassDef>(def))
      return visitClassDef(*classDef);
    assert(false);
    return T();
  }

  virtual T visitFunctionDef(FunctionDef &functionDef) = 0;
  virtual T visitClassDef(ClassDef &classDef) = 0;

  virtual T visitBlock(Block &block) {
    for (Stmt* stmt : block.stmts)
      visitStmt(*stmt);
    return T();
  }


  virtual T visitStmt(Stmt &stmt) {
    if (isa<EmptyStmt>(stmt))
      return T();
    if (auto *blockStmt = dyn_cast<BlockStmt>(stmt))
      return visitBlockStmt(*blockStmt);
    if (auto *declStmt = dyn_cast<DeclStmt>(stmt))
      return visitDeclStmt(*declStmt);
    if (auto *assignStmt = dyn_cast<AssignStmt>(stmt))
      return visitAssignStmt(*assignStmt);
    if (auto *incrStmt = dyn_cast<IncrStmt>(stmt))
      return visitIncrStmt(*incrStmt);
    if (auto *decrStmt = dyn_cast<DecrStmt>(stmt))
      return visitDecrStmt(*decrStmt);
    if (auto *retStmt = dyn_cast<ReturnStmt>(stmt))
      return visitReturnStmt(*retStmt);
    if (auto *ifStmt = dyn_cast<IfStmt>(stmt))
      return visitIfStmt(*ifStmt);
    if (auto *whileStmt = dyn_cast<WhileStmt>(stmt))
      return visitWhileStmt(*whileStmt);
    if (auto *exprStmt = dyn_cast<ExprStmt>(stmt))
      return visitExprStmt(*exprStmt);

    llvm_unreachable("Unhandled stmt");
  }

  virtual T visitBlockStmt(BlockStmt &blockStmt) {
    return visitBlock(blockStmt.block);
  }

  virtual T visitDeclStmt(DeclStmt &declStmt) = 0;
  virtual T visitAssignStmt(AssignStmt &assignStmt) {
    return visitExpr(*assignStmt.initializer);
  }

  virtual T visitIncrStmt(IncrStmt &incrStmt) = 0;
  virtual T visitDecrStmt(DecrStmt &incrStmt) = 0;
  virtual T visitReturnStmt(ReturnStmt &returnStmt) = 0;
  virtual T visitIfStmt(IfStmt &condStmt) = 0;
  virtual T visitWhileStmt(WhileStmt &whileStmt) = 0;
  virtual T visitExprStmt(ExprStmt &exprStmt) {
    return visitExpr(*exprStmt.expr);
  }

  virtual T visitExpr(Expr &expr) {
    if (auto *unExpr = dyn_cast<UnaryExpr>(expr))
      return visitUnaryExpr(*unExpr);
    if (auto *binExpr = dyn_cast<BinExpr>(expr))
      return visitBinExpr(*binExpr);
    if (auto *varExpr = dyn_cast<VarExpr>(expr))
      return visitVarExpr(*varExpr);
    if (auto *constIntExpr = dyn_cast<ConstIntExpr>(expr))
      return visitConstIntExpr(*constIntExpr);
    if (auto *booleanExpr = dyn_cast<BooleanExpr>(expr))
      return visitBooleanExpr(*booleanExpr);
    if (auto *callExpr = dyn_cast<CallExpr>(expr))
      return visitCallExpr(*callExpr);
    if (auto *constStringExpr = dyn_cast<ConstStringExpr>(expr))
      return visitConstStringExpr(*constStringExpr);
    if (auto *parenExpr = dyn_cast<ParenExpr>(expr))
      return visitParenExpr(*parenExpr);
    llvm_unreachable("Unhandled expr");
  }

  virtual T visitUnaryExpr(UnaryExpr &unaryExpr) = 0;
  virtual T visitBinExpr(BinExpr &binExpr) = 0;
  virtual T visitVarExpr(VarExpr &varExpr) = 0;
  virtual T visitConstIntExpr(ConstIntExpr &constIntExpr) = 0;
  virtual T visitBooleanExpr(BooleanExpr &booleanExpr) = 0;
  virtual T visitCallExpr(CallExpr &callExpr) = 0;
  virtual T visitConstStringExpr(ConstStringExpr &constStringExpr) = 0;
  virtual T visitParenExpr(ParenExpr &parenExpr) {
    return visitExpr(*parenExpr.expr);
  }
};




