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
  std::string name;
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

struct DeclStmt;

struct DeclItem {
  std::string name;
  Expr* initializer;
  DeclStmt *parent;
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

struct ReturnStmt : Stmt {
  ReturnStmt(Expr *expr) : expr(expr) {}
  Expr *expr;

  std::string dump() const override {
    return "ReturnStmt";
  }
};

struct IfStmt : Stmt {
  IfStmt(Expr *condition, Stmt *stmt, Stmt *elseStmt)
      : condition(condition), stmt(stmt), elseStmt(elseStmt) {}

  Expr *condition;
  Stmt *stmt;
  Stmt *elseStmt;

  std::string dump() const override {
    return "IfStmt";
  }
};

struct WhileStmt : Stmt {
  WhileStmt(Expr *cond, Stmt *stmt)
      : condition(cond), stmt(stmt) {}

  Expr *condition;
  Stmt *stmt;

  std::string dump() const override {
    return "WhileStmt";
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
  enum class BinOp : uint8_t {
    // Relation operators
    LESS,
    LESS_EQ,
    GREATER,
    GREATER_EQ,
    EQUALS,
    NOT_EQUALS,

    // mul operators
    Mul,
    Div,
    Mod,

    // add operators
    Add,
    Minus,

    // Boolean opeartors
    And,
    Or,
  };


  BinExpr(Type* type, BinOp binOp, Expr *lhs, Expr* rhs)
  : Expr(type), binOp(binOp), lhs(lhs), rhs(rhs) {}

  BinOp binOp;
  Expr *lhs, *rhs;

  std::string dump() const override {
    return "BinExpr:";
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


