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

  virtual T visitDeclStmt(DeclStmt &declStmt) {
    for (DeclItem &declItem : declStmt.decls)
      visitDeclItem(declItem);
    return {};
  }

  virtual T visitDeclItem(DeclItem &declItem) = 0;

  virtual T visitAssignStmt(AssignStmt &assignStmt) {
    return visitExpr(*assignStmt.initializer);
  }

  virtual T visitReturnStmt(ReturnStmt &returnStmt) = 0;
  virtual T visitIfStmt(IfStmt &condStmt) = 0;
  virtual T visitWhileStmt(WhileStmt &whileStmt) = 0;


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
    llvm_unreachable("Unhandled expr");
  }

  virtual T visitBinExpr(BinExpr &binExpr) = 0;

  virtual T visitVarExpr(VarExpr &varExpr) = 0;
  virtual T visitConstIntExpr(ConstIntExpr &constIntExpr) = 0;
  virtual T visitBooleanExpr(BooleanExpr &booleanExpr) = 0;

};




