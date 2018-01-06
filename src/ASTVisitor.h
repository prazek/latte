#pragma once

#include "AST.h"


template <typename T>
class ASTVisitor {

public:
  virtual T visitAST(AST& ast) {
    for (Def *def : ast.definitions)
      visitDef(*def);
    return {};
  }

  virtual T visitDef(Def &def) {
    if (auto *funDef = dyn_cast<FunctionDef>(def))
      return visitFunctionDef(*funDef);
    if (auto *classDef = dyn_cast<ClassDef>(def))
      return visitClassDef(*classDef);
    assert(false);
    return {};
  }

  virtual T visitFunctionDef(FunctionDef &functionDef) = 0;
  virtual T visitClassDef(ClassDef &classDef) = 0;

  virtual T visitBlock(Block &block) {
    for (Stmt* stmt : block.stmts)
      visitStmt(*stmt);
    return {};
  }


  virtual T visitStmt(Stmt &stmt) {
    if (isa<EmptyStmt>(stmt))
      return {};
    if (auto *blockStmt = dyn_cast<BlockStmt>(stmt))
      return visitBlockStmt(*blockStmt);
    if (auto *declStmt = dyn_cast<DeclStmt>(stmt))
      return visitDeclStmt(*declStmt);
    if (auto *assignStmt = dyn_cast<AssignStmt>(stmt))
      return visitAssignStmt(*assignStmt);
    if (auto *exprStmt = dyn_cast<ExprStmt>(stmt))
      return visitExprStmt(*exprStmt);

    assert(false);
    return {};
  }

  virtual T visitBlockStmt(BlockStmt &blockStmt) {
    return visitBlock(blockStmt.block);
  }

  virtual T visitDeclStmt(DeclStmt &declStmt) {
    for (DeclItem &declItem : declStmt.decls)
      visitDeclItem(declItem);
    return {};
  }

  virtual T visitDeclItem(DeclItem &declItem) = 0;

  virtual T visitAssignStmt(AssignStmt &assignStmt) {
    return visitExpr(*assignStmt.initializer);
  }

  virtual T visitExprStmt(ExprStmt &exprStmt) {
    return visitExpr(*exprStmt.expr);
  }

  virtual T visitExpr(Expr &expr) {
    if (auto *binExpr = dyn_cast<BinExpr>(expr))
      return visitBinExpr(*binExpr);
    if (auto *varExpr = dyn_cast<VarExpr>(expr))
      return visitVarExpr(*varExpr);
    if (auto *constIntExpr = dyn_cast<ConstIntExpr>(expr))
      return visitConstIntExpr(*constIntExpr);
    if (auto *booleanExpr = dyn_cast<BooleanExpr>(expr))
      return visitBooleanExpr(*booleanExpr);
    assert(false);
    return {};
  }

  virtual T visitBinExpr(BinExpr &binExpr) {
    if (auto *mulExpr = dyn_cast<MulExpr>(binExpr))
      return visitMulExpr(*mulExpr);
    if (auto *addExpr = dyn_cast<AddExpr>(binExpr))
      return visitAddExpr(*addExpr);
    assert(false);
    return {};
  }

  virtual T visitMulExpr(MulExpr &mulExpr) {
    visitExpr(*mulExpr.lhs);
    visitExpr(*mulExpr.rhs);
    return {};
  }

  virtual T visitAddExpr(AddExpr &addExpr) {
    visitExpr(*addExpr.lhs);
    visitExpr(*addExpr.rhs);
    return {};
  }

  virtual T visitVarExpr(VarExpr &varExpr) = 0;
  virtual T visitConstIntExpr(ConstIntExpr &constIntExpr) = 0;
  virtual T visitBooleanExpr(BooleanExpr &booleanExpr) = 0;

};




