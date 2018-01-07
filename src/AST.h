#pragma once

#include <vector>
#include "Type.h"

struct Def;
struct FunctionDef;
struct Block;
struct Stmt;
struct Expr;
struct VarDecl;

struct AST {
  std::vector<Def*> definitions;
};

struct Def {
  Def(Type *type) : type(type) {}

  Type *type;
  virtual std::string dump() const = 0;
};

struct Block {
  std::vector<Stmt*> stmts;

  std::string dump() const {
    return "Block TODO";
  }
};

struct FunctionDef final : Def {
  FunctionDef(FunctionType *type, std::string name)
      : Def(type), name(std::move(name)) {}

  std::vector<VarDecl*> arguments;
  std::string name;
  Block block;

  FunctionType *getFunType() {
    return cast<FunctionType>(type);
  }

  std::string dump() const override {
    return "FunctionDef";
  }
};

struct ClassDef final : Def {
  ClassDef() : Def(nullptr) {}


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

struct VarDecl final : Def {
  VarDecl(std::string name, Type* type, Expr *initializer)
      : Def(type), name(std::move(name)), initializer(initializer) {}

  std::string name;
  Expr* initializer;

  std::string dump() const override {
    return "VarDecl: " + name;
  }
};

struct DeclStmt : public Stmt {
  Type *type;
  std::vector<VarDecl*> decls;

  std::string dump() const override {
    return "DeclStmt";
  }
};


struct AssignStmt : Stmt {
  AssignStmt(VarDecl *decl, Expr *expr)
      : decl(decl),
        initializer(expr) {}

  VarDecl *decl;
  Expr *initializer;


  std::string dump() const override {
    return "AssignStmt";
  }
};

struct IncrStmt : Stmt {
  IncrStmt(VarDecl *decl)
      : varDecl(decl) {}

  VarDecl *varDecl;

  std::string dump() const override {
    return "IncrStmt:";
  }
};

struct DecrStmt : Stmt {
  DecrStmt(VarDecl *decl)
      : varDecl(decl) {}

  VarDecl *varDecl;

  std::string dump() const override {
    return "IncrStmt:";
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

struct UnaryExpr : Expr {
  enum class UnOp : uint8_t {
    Minus,
    Neg
  };

  UnaryExpr(Type *type, UnOp unOp, Expr *expr)
      : Expr(type), unOp(unOp), expr(expr) {}

  UnOp unOp;
  Expr *expr;
  std::string dump() const override {
    return "UnaryExpr:";
  }
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
  VarExpr(VarDecl *decl) : Expr(decl->type) , decl(decl){}
  VarDecl *decl;

  std::string dump() const override {
    return "VarExpr:" + decl->name;
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

struct CallExpr : Expr {
  CallExpr(FunctionDef *callee)
      : Expr(callee->getFunType()->returnType), callee(callee) {}


  std::vector<Expr*> arguments;
  FunctionDef *callee;

  std::string dump() const override {
    return "CallExpr";
  }
};

struct ConstStringExpr : Expr {
  ConstStringExpr(Type *type, std::string string)
      : Expr(type), string(std::move(string)) {}

  std::string string;

  std::string dump() const override {
    return "ConstStringExpr:";
  }
};

struct ParenExpr : Expr {
  ParenExpr(Expr *expr) : Expr(expr->type) {}

  Expr *expr;

  std::string dump() const override {
    return "ParenExpr:";
  }
};


