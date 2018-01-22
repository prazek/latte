#pragma once

#include "AST.h"
inline Expr* getDefaultInitializer(Type &type) {

  if (auto *simpleType = dyn_cast<SimpleType>(type)) {
    switch (simpleType->pod) {
      case SimpleType::POD::Bool:
        return new BooleanExpr(false);
      case SimpleType::POD::Int:
        return new ConstIntExpr(0);
      case SimpleType::POD::String:
        return new ConstStringExpr(""); // TODO null
      case SimpleType::POD::Null:
      case SimpleType::POD::Void:
        llvm_unreachable("no null expr");
    }
  }
  if (auto *classType = dyn_cast<ClassType>(type))
    return new ClassCastExpr(classType, new NullExpr);

  llvm_unreachable("Unhandled type");
}

inline Expr *getAsRValue(Expr *expr) {
  if (!expr)
    return expr;
  if (isa<VarExpr>(expr) || isa<MemberExpr>(expr))
    return new RValueImplicitCast(expr->type, expr);
  // No cast needed.
  return expr;
}
