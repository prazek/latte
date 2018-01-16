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

  FunctionType *getFunType() const {
    return cast<FunctionType>(type);
  }

  std::string dump() const override {
    return "FunctionDef";
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

struct FieldDecl final : Def {
  FieldDecl(std::string name, Type *type)
      : Def(type), name(std::move(name)) {}

  std::string name;
  int offset;

  std::string dump() const override {
    return "FieldDecl:";
  }
};

struct ClassDef final : Def {
  ClassDef(std::string className, ClassType *classType)
      : Def(classType),
        type(new ClassType(className)),
        className(std::move(className)) {}


  ClassType *type;
  ClassDef *baseClass = nullptr;
  std::string className;
  // FieldDecl?
  std::vector<FieldDecl*> fieldDecls;
  //std::vector<FunctionDef*> methodDecls;


  FieldDecl *getFieldWithName(const std::string& name) {
    for (auto *fieldDecl : fieldDecls)
      if (fieldDecl->name == name)
        return fieldDecl;
    return nullptr;
  }

  ClassType *getClassType() const {
    return cast<ClassType>(type);
  }

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



struct DeclStmt : public Stmt {
  Type *type;
  std::vector<VarDecl*> decls;

  std::string dump() const override {
    return "DeclStmt";
  }
};


struct AssignStmt : Stmt {
  AssignStmt(Expr *lhs, Expr *rhs)
      : lhs(lhs),
        initializer(rhs) {}


  Expr *lhs;
  Expr *initializer;
  std::string dump() const override {
    return "AssignStmt";
  }
};

struct IncrStmt : Stmt {
  IncrStmt(Expr *lhs)
      : lhs(lhs) {}


  Expr *lhs;
  std::string dump() const override {
    return "IncrStmt:";
  }
};

struct DecrStmt : Stmt {
  DecrStmt(Expr *expr)
      : expr(expr) {}

  Expr *expr;

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

// This stmt is inserted at the end of non-void function that does not have a
// return, meaning that getting there is unreachable.
struct UnreachableStmt : Stmt {

  std::string dump() const override {
    return "UnreachableStmt";
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

struct RValueImplicitCast : Expr {
  RValueImplicitCast(Type *type, Expr *expr)
      : Expr(type), expr(expr) {}

  Expr *expr;

  std::string dump() const override {
    return "RValueImplicitCast:";
  }
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

struct NewExpr : Expr {
  NewExpr(ClassType *type) : Expr(type) {}


  ClassType *getClassType() const {
    return cast<ClassType>(type);
  }
  std::string dump() const override {
    return "NewExpr:";
  }
};

struct ClassCastExpr : Expr {
  ClassCastExpr(ClassType *type, Expr *casted)
      : Expr(type), casted(casted) {}

  Expr *casted;

  std::string dump() const override {
    return "ClassCastExpr:";
  }
};

struct MemberExpr : Expr {
  MemberExpr(Expr *thisPtr, FieldDecl *fieldDecl)
  : Expr(fieldDecl->type), thisPtr(thisPtr), fieldDecl(fieldDecl) {}

  Expr *thisPtr;
  FieldDecl *fieldDecl;
  std::string dump() const override {
    return "MemberExpr:";
  }
};

/*
struct MemberFunExpr : Expr {
  MemberFunExpr(Expr *thisPtr, ClassDef *classDef, FunctionDef *funDef)
      : Expr()
};
*/

struct VarExpr : Expr {
  VarExpr(VarDecl *decl) : Expr(decl->type), decl(decl){}
  VarDecl *decl;

  std::string dump() const override {
    return "VarExpr:" + decl->name;
  }
};



struct FunExpr : Expr {
  FunExpr(FunctionDef *def) : Expr(def->type), def(def) {}

  FunctionDef *def;
  std::string dump() const override {
    return "FunExpr:";
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
  CallExpr(Expr *expr, Type *returnType)
      : Expr(returnType), callee(expr) {}


  std::vector<Expr*> arguments;
  Expr *callee;

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


