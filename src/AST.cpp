#include "AST.h"
#include <sstream>

static std::string makeIdent(int ident) {
  return std::string(ident, ' ');
}


std::string AST::dump() const {
  std::stringstream ss;
  for (auto *def : definitions)
    ss << def->dump();
  return ss.str();
}


std::string FunctionDef::dump(int ident) const {
    std::stringstream ss;

    ss << makeIdent(ident) << "FunctionDef: " + name + "\n";
    for (auto *arg : arguments)
      ss << arg->dump(ident + 2);

    ss << block.dump(ident + 2);
    return ss.str();
}

std::string VarDecl::dump(int ident) const {
  return makeIdent(ident) + "VarDecl: " + type->toString() + " " + name + "\n" +
      (initializer? initializer->dump(ident) : "");
}

std::string Block::dump(int ident) const {
  std::stringstream ss;
  ss << makeIdent(ident) << "Block:\n";
  for (auto *stmt : stmts)
    ss << stmt->dump(ident + 2);

  return ss.str();
}
std::string FieldDecl::dump(int ident) const {
  return makeIdent(ident) + "FieldDecl: " + type->toString() + " "+  name + "\n";
}
std::string ClassDef::dump(int ident) const {
  std::stringstream ss;
  ss << makeIdent(ident) << "ClassDef: " << className << "\n";
  for (auto *field : fieldDecls)
    ss << field->dump(ident + 2);
  for (auto *method : methodDecls)
    ss << method->dump(ident + 2);

  return ss.str();
}
FunctionDef *ClassDef::getFunctionWithName(const std::string &name) const {
  for (auto *methodDecl : methodDecls)
    if (methodDecl->name == name)
      return methodDecl;
  return nullptr;
}
FieldDecl *ClassDef::getFieldWithName(const std::string &name) const {
  for (auto *fieldDecl : fieldDecls)
    if (fieldDecl->name == name)
      return fieldDecl;
  return nullptr;
}
std::string BlockStmt::dump(int ident) const {
  return "BlockStmt:\n" + block.dump(ident + 2);
}
std::string DeclStmt::dump(int ident) const {
  std::stringstream ss;
  ss << makeIdent(ident) + "DeclStmt:\n";
  for (auto *decl : decls)
    ss << decl->dump(ident + 2);
  return ss.str();

}
std::string BooleanExpr::dump(int ident) const {
  std::stringstream ss;
  ss << makeIdent(ident) << "BooleanExpr:" << value;
  return ss.str();
}
std::string EmptyStmt::dump(int ident) const {
  return makeIdent(ident) + "EmptyStmt\n";

}
std::string AssignStmt::dump(int ident) const {
  return makeIdent(ident) + "AssignStmt:\n";
}
std::string IncrStmt::dump(int ident) const {
  return makeIdent(ident) + "IncrStmt:\n";
}
std::string DecrStmt::dump(int ident) const {
  return makeIdent(ident) + "IncrStmt:\n";
}
std::string ReturnStmt::dump(int ident) const {
  return makeIdent(ident) + "ReturnStmt:\n";
}
std::string UnreachableStmt::dump(int ident) const {
  return makeIdent(ident) + "UnreachableStmt:\n";
}
std::string IfStmt::dump(int ident) const {
  return makeIdent(ident) + "IfStmt:\n";
}
std::string WhileStmt::dump(int ident) const {
  return makeIdent(ident) + "WhileStmt:\n";
}
std::string ExprStmt::dump(int ident) const {
  return makeIdent(ident) + "ExprStmt:\n" +
      expr->dump(ident + 2);
}
std::string RValueImplicitCast::dump(int ident) const {
  return makeIdent(ident) + "RValueImplicitCast:\n"
      + expr->dump(ident + 2);
}
std::string UnaryExpr::dump(int ident) const {
  return makeIdent(ident) + "UnaryExpr:\n";
}
std::string BinExpr::dump(int ident) const {
  return makeIdent(ident) + "BinExpr:\n";
}
std::string NewExpr::dump(int ident) const {
  return makeIdent(ident) + "NewExpr:\n";
}
std::string ClassCastExpr::dump(int ident) const {
  return makeIdent(ident) + "ClassCastExpr:\n";
}
std::string MemberExpr::dump(int ident) const {
  return makeIdent(ident) + "MemberExpr:\n"
      + thisPtr->dump(ident + 2) + "\n" + fieldDecl->dump(ident + 2);
}
std::string VarExpr::dump(int ident) const {
  return makeIdent(ident) + "VarExpr: " + decl->name + "\n";
}
std::string MethodExpr::dump(int ident) const {
  return makeIdent(ident) + "MethodExpr:\n"
      + thisPtr->dump(ident + 2) + funDef->dump(ident + 2);
}
std::string FunExpr::dump(int ident) const {
  return makeIdent(ident) + "FunExpr:";
}
std::string ConstIntExpr::dump(int ident) const {
  return makeIdent(ident) + "ConstIntExpr:" + std::to_string(value);
}
std::string VTableExpr::dump(int ident) const {
  return makeIdent(ident) + "VTableExpr:\n" + classDef->dump(ident + 2);
}
std::string CallExpr::dump(int ident) const {
  return makeIdent(ident) + "CallExpr\n";
}
std::string MemberCallExpr::dump(int ident) const {
  std::stringstream ss;
  ss << makeIdent(ident) << "MemberCallExpr:\n"
      << thisPtr->dump(ident + 2)
      << callee->dump(ident + 2);

  ss << makeIdent(ident + 2) << "arguments:\n";
  for (auto *arg : arguments)
    ss << arg->dump(ident + 4);
  return ss.str();
}
std::string ConstStringExpr::dump(int ident) const {
  return makeIdent(ident) + "ConstStringExpr: " + string + "\n";
}
std::string NullExpr::dump(int ident) const {
  return makeIdent(ident) + "NullExpr\n";
}
std::string ParenExpr::dump(int ident) const {
  return makeIdent(ident) + "ParenExpr:\n" + expr->dump(ident + 2);
}
