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

  std::string dump() const;
};

struct Def {
  Def(Type *type) : type(type) {}

  Type *type;
  virtual std::string dump(int ident = 0) const = 0;
};


struct Stmt {
  virtual std::string dump(int ident) const = 0;
};

struct Block {
  std::vector<Stmt*> stmts;

  std::string dump(int ident) const;
};

struct FunctionDef final : Def {
  FunctionDef(FunctionType *type, std::string name)
      : Def(type), name(std::move(name)) {}

  // Additional data for methods. FIXME: get them out of here.
  VarDecl *thisPtr;
  unsigned methodID;


  std::vector<VarDecl*> arguments;
  std::string name;
  Block block;

  FunctionType *getFunType() const {
    return cast<FunctionType>(type);
  }

  std::string dump(int ident) const override;
};

struct FieldDecl final : Def {
  FieldDecl(std::string name, Type *type)
      : Def(type), name(std::move(name)) {}

  std::string name;
  unsigned fieldId;

  std::string dump(int ident) const override;
};


struct VarDecl final : Def {
  VarDecl(std::string name, Type* type, Expr *initializer)
      : Def(type), name(std::move(name)), initializer(initializer) {}

  std::string name;
  Expr* initializer;

  std::string dump(int ident) const override;
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
  std::vector<FunctionDef*> methodDecls;


  FieldDecl *getFieldWithName(const std::string& name) const;

  FunctionDef *getFunctionWithName(const std::string &name) const;


  std::string dump(int ident) const override;
};


struct EmptyStmt : public Stmt {
  std::string dump(int ident) const override;
};

struct BlockStmt : public Stmt {
  Block block;
  std::string dump(int ident) const override;
};



struct DeclStmt : public Stmt {
  Type *type;
  std::vector<VarDecl*> decls;

  std::string dump(int ident) const override;
};


struct AssignStmt : Stmt {
  AssignStmt(Expr *lhs, Expr *rhs)
      : lhs(lhs),
        initializer(rhs) {}


  Expr *lhs;
  Expr *initializer;
  std::string dump(int ident) const override;
};

struct IncrStmt : Stmt {
  IncrStmt(Expr *lhs)
      : lhs(lhs) {}


  Expr *lhs;
  std::string dump(int ident) const override;
};

struct DecrStmt : Stmt {
  DecrStmt(Expr *expr)
      : expr(expr) {}

  Expr *expr;

  std::string dump(int ident) const override;
};


struct ReturnStmt : Stmt {
  ReturnStmt(Expr *expr) : expr(expr) {}
  Expr *expr;

  std::string dump(int ident) const override;
};

// This stmt is inserted at the end of non-void function that does not have a
// return, meaning that getting there is unreachable.
struct UnreachableStmt : Stmt {

  std::string dump(int ident) const override;
};

struct IfStmt : Stmt {
  IfStmt(Expr *condition, Stmt *stmt, Stmt *elseStmt)
      : condition(condition), stmt(stmt), elseStmt(elseStmt) {}

  Expr *condition;
  Stmt *stmt;
  Stmt *elseStmt;

  std::string dump(int ident) const override;
};

struct WhileStmt : Stmt {
  WhileStmt(Expr *cond, Stmt *stmt)
      : condition(cond), stmt(stmt) {}

  Expr *condition;
  Stmt *stmt;

  std::string dump(int ident) const override;
};

struct ExprStmt : Stmt {
  ExprStmt(Expr *expr) : expr(expr) {}
  Expr *expr;

  std::string dump(int ident) const override;
};

struct Expr {
  Expr(Type *type) : type(type) {}
  Type *type;

  virtual std::string dump(int ident) const = 0;
};

struct RValueImplicitCast : Expr {
  RValueImplicitCast(Type *type, Expr *expr)
      : Expr(type), expr(expr) {}

  Expr *expr;

  std::string dump(int ident) const override;
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
  std::string dump(int ident) const override;
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

  std::string dump(int ident) const override;

};

struct NewExpr : Expr {
  NewExpr(ClassType *type) : Expr(type) {}


  ClassType *getClassType() const {
    return cast<ClassType>(type);
  }
  std::string dump(int ident) const override;
};

struct ClassCastExpr : Expr {
  ClassCastExpr(ClassType *type, Expr *casted)
      : Expr(type), casted(casted) {}

  Expr *casted;

  std::string dump(int ident) const override;
};

struct MemberExpr : Expr {
  MemberExpr(Expr *thisPtr, FieldDecl *fieldDecl)
  : Expr(fieldDecl->type), thisPtr(thisPtr), fieldDecl(fieldDecl) {}

  Expr *thisPtr;
  FieldDecl *fieldDecl;
  std::string dump(int ident) const override;
};

struct VarExpr : Expr {
  VarExpr(VarDecl *decl) : Expr(decl->type), decl(decl) {}
  VarDecl *decl;

  std::string dump(int ident) const override;
};

struct MethodExpr : Expr {
  MethodExpr(Expr *thisPtr, FunctionDef *funDef)
      : Expr(funDef->type), thisPtr(thisPtr), funDef(funDef) {}

  Expr *thisPtr;
  FunctionDef *funDef;

  std::string dump(int ident) const override;
};


struct FunExpr : Expr {
  FunExpr(FunctionDef *def) : Expr(def->type), def(def) {}

  FunctionDef *def;
  std::string dump(int ident) const override;
};

struct ConstIntExpr : Expr {
  ConstIntExpr(int32_t value) : Expr(SimpleType::Int()), value(value) {}
  int32_t value;

  std::string dump(int ident) const override;
};

struct BooleanExpr : Expr {
  BooleanExpr(bool value) : Expr(SimpleType::Bool()), value(value) {}
  bool value;

  std::string dump(int ident) const override;
};

struct VTableExpr : Expr {
  VTableExpr(ClassDef *classDef)
      : Expr(new VptrType), classDef(classDef) {}

  ClassDef *classDef;
  std::string dump(int ident) const override;
};

struct CallExpr : Expr {
  CallExpr(Expr *expr, Type *returnType)
      : Expr(returnType), callee(expr) {}


  std::vector<Expr*> arguments;
  Expr *callee;

  std::string dump(int ident) const override;
};

struct MemberCallExpr : Expr {
  MemberCallExpr(Expr *thisPtr, Expr *callee, Type *returnType)
    : Expr(returnType), thisPtr(thisPtr), callee(callee) {}

  Expr *thisPtr;
  Expr *callee;
  std::vector<Expr*> arguments;


  std::string dump(int ident) const override;
};

struct ConstStringExpr : Expr {
  ConstStringExpr(std::string string)
      : Expr(SimpleType::String()), string(std::move(string)) {}

  std::string string;

  std::string dump(int ident) const override;
};

struct NullExpr : Expr {
  NullExpr() : Expr(SimpleType::Null()) {}

  std::string dump(int ident) const override;
};

struct ParenExpr : Expr {
  ParenExpr(Expr *expr) : Expr(expr->type) {}

  Expr *expr;

  std::string dump(int ident) const override;
};


