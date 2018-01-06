#pragma once

#include <vector>
#include "Type.h"

struct Def;
struct FunctionDef;
struct Block;
struct Stmt;
struct Expr;


struct AST {
  std::vector<Def*> definitions;
};

struct Def {
  virtual std::string dump() const = 0;
};

struct ArgDecl {
  Type *type;
  std::string name;
};

struct Block {
  std::vector<Stmt*> stmts;

  std::string dump() const {
    return "Block TODO";
  }
};

struct FunctionDef final : Def {
  FunctionType *functionType;
  std::vector<ArgDecl> arguments;
  Block block;

  std::string dump() const override {
    return "FunctionDef";
  }
};

struct ClassDef final : Def {
  std::string dump() const override {
    return "ClassDef";
  }
};


struct Stmt {
  virtual std::string dump() const = 0;
};

struct EmptyStmt : public Stmt {
  std::string dump() const override {
    return "EmptyStmt";
  }
};

struct BlockStmt : public Stmt {
  Block block;
  std::string dump() const override {
    return "BlockStmt" + block.dump();
  }
};

struct DeclItem {
  std::string name;
  Expr* initializer;
};

struct DeclStmt : public Stmt {
  Type *type;
  std::vector<DeclItem> decls;

  std::string dump() const override {
    return "DeclStmt";
  }
};


struct AssignStmt : Stmt {
  AssignStmt(std::string name, Expr *expr) : name(std::move(name)),
                                             initializer(expr) {}
  std::string name;
  Expr *initializer;


  std::string dump() const override {
    return "AssignStmt";
  }
};

struct ExprStmt : Stmt {
  ExprStmt(Expr *expr) : expr(expr) {}
  Expr *expr;

  std::string dump() const override {
    return "ExprStmt";
  }
};

struct Expr {
  Expr(Type *type) : type(type) {}
  Type *type;

  virtual std::string dump() const = 0;
};

struct BinExpr : Expr {
  BinExpr(Type* type, char mulOp, Expr *lhs, Expr* rhs)
  : Expr(type), mulOp(mulOp), lhs(lhs), rhs(rhs) {}


  char mulOp;
  Expr *lhs, *rhs;
};

struct MulExpr : BinExpr {
  MulExpr(Type* type, char mulOp, Expr *lhs, Expr* rhs)
      : BinExpr(type, mulOp, lhs, rhs) {}


  std::string dump() const override {
    return "MulExpr:" + mulOp + lhs->dump() + rhs->dump();
  }
};

struct AddExpr : BinExpr {
  AddExpr(Type* type, char addOp, Expr *lhs, Expr* rhs)
    : BinExpr(type, addOp, lhs, rhs) {}

  std::string dump() const override {
    return "AddExpr:" + mulOp + lhs->dump() + rhs->dump();
  }
};

struct VarExpr : Expr {
  VarExpr(Type* type, std::string name) : Expr(type), name(std::move(name)) {}
  std::string name;

  std::string dump() const override {
    return "VarExpr:" + name;
  }
};

struct ConstIntExpr : Expr {
  ConstIntExpr(Type* type, int32_t value) : Expr(type), value(value) {}
  int32_t value;

  std::string dump() const override {
    return "ConstIntExpr:" + value;
  }
};

struct BooleanExpr : Expr {
  BooleanExpr(Type* type, bool value) : Expr(type), value(value) {}
  bool value;

  std::string dump() const override {
    return "BooleanExpr:" + value;
  }
};


