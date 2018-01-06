
#include "TypeChecker.h"
#include "Type.h"
#include "Utilities.h"
#include <memory>

static Type* getBool() {
  return new SimpleType{SimpleType::POD::Bool};
}

static Type* getVoid() {
  return new SimpleType{SimpleType::POD::Void};
}

static Type* getInt() {
  return new SimpleType{SimpleType::POD::Int};
}

static Type* getStr() {
  return new SimpleType{SimpleType::POD::String};
}

antlrcpp::Any TypeChecker::visitBool(LatteParser::BoolContext *) {
  return getBool();
}
antlrcpp::Any TypeChecker::visitVoid(LatteParser::VoidContext *) {
  return getVoid();
}
antlrcpp::Any TypeChecker::visitInt(LatteParser::IntContext *) {
  return getInt();
}
antlrcpp::Any TypeChecker::visitStr(LatteParser::StrContext *) {
  return getStr();
}


static bool isIntegral(const Type& type) {
  if (auto *st = dyn_cast<SimpleType>(type))
    return st->isInt();
  return false;
}

static bool isBoolean(const Type& type) {
  if (auto *st = dyn_cast<SimpleType>(type))
    return st->isBool();
  return false;
}

static bool isVoid(const Type& type) {
  if (auto *st = dyn_cast<SimpleType>(type))
    return st->isVoid();
  return false;
}


antlrcpp::Any TypeChecker::visitEMulOp(LatteParser::EMulOpContext *ctx) {
  assert(ctx->children.size() == 3);
  auto *lhs = ctx->children.at(0);
  Expr *lhsExpr = visit(lhs);
  auto *rhs = ctx->children.at(2);
  Expr* rhsExpr = visit(rhs);

  auto getMulOp = [](const auto &op) {
    if (op == "*")
      return BinExpr::BinOp::Mul;
    if (op == "/")
      return BinExpr::BinOp::Div;
    if (op == "%")
      return BinExpr::BinOp::Mod;
    llvm_unreachable("Unknown op");
  };

  auto *mulExpr = new BinExpr(getInt(), getMulOp(ctx->children.at(1)->getText()),
                              lhsExpr, rhsExpr);

  if (lhsExpr->type == nullptr || rhsExpr->type == nullptr)
      return (Expr*)mulExpr;

  if (!isIntegral(*lhsExpr->type) || !isIntegral(*rhsExpr->type)) {
    std::string op = ctx->children.at(1)->getText();
    context.diagnostic.issueError("Cannot perform operation '" + op
                                    + "' on type '" + lhsExpr->type->toString() + "' and '"
                                    + rhsExpr->type->toString() + "'", ctx);
    return (Expr*)mulExpr;
  }

  assert(*lhsExpr->type == *rhsExpr->type && "Only ints here");

  return (Expr*)mulExpr;
}

antlrcpp::Any TypeChecker::visitEAddOp(LatteParser::EAddOpContext *ctx) {
  // TODO handle strings concat?
  assert(ctx->children.size() == 3);
  auto *lhs = ctx->children.at(0);
  Expr *lhsExpr = visit(lhs);
  auto *rhs = ctx->children.at(2);
  Expr* rhsExpr = visit(rhs);

  auto getAddOp = [](const auto &op) {
    if (op == "+")
      return BinExpr::BinOp::Add;
    if (op == "-")
      return BinExpr::BinOp::Minus;
    llvm_unreachable("Unknown op");
  };

  auto addExpr = new BinExpr(getInt(), getAddOp(ctx->children.at(1)->getText()),
                             lhsExpr, rhsExpr);

  if (lhsExpr->type == nullptr || lhsExpr->type == nullptr)
    return (Expr*)addExpr;

  if (!isIntegral(*lhsExpr->type) || !isIntegral(*rhsExpr->type)) {
    std::string op = ctx->children.at(1)->getText();
    context.diagnostic.issueError("Cannot perform operation '" + op
                                    + "' on type '" + lhsExpr->type->toString() + "' and '"
                                    + rhsExpr->type->toString() + "'", ctx);
    return (Expr*)addExpr;
  }

  assert(*lhsExpr->type == *rhsExpr->type && "Only ints here");
  return (Expr*)addExpr;
}

antlrcpp::Any TypeChecker::visitERelOp(LatteParser::ERelOpContext *ctx) {
  assert(ctx->children.size() == 3);
  auto *lhs = ctx->children.at(0);
  Expr *lhsExpr = visit(lhs);
  auto *rhs = ctx->children.at(2);
  Expr* rhsExpr = visit(rhs);

  auto getRelOp = [](const auto &op) {
    if (op == "<")
      return BinExpr::BinOp::LESS;
    if (op == "<=")
      return BinExpr::BinOp::LESS_EQ;
    if (op == ">")
      return BinExpr::BinOp::GREATER;
    if (op == ">=")
      return BinExpr::BinOp::GREATER_EQ;
    if (op == "==")
      return BinExpr::BinOp::EQUALS;
    if (op == "!=")
      return BinExpr::BinOp::NOT_EQUALS;
    llvm_unreachable("Unknown op");
  };

  auto *binExpr = new BinExpr(getBool(), getRelOp(ctx->children.at(1)->getText()),
                              lhsExpr, rhsExpr);

  if (lhsExpr->type == nullptr || lhsExpr->type == nullptr)
    return (Expr*)binExpr;

  // TODO handle string
  if (!isIntegral(*lhsExpr->type) || !isIntegral(*rhsExpr->type)) {
    std::string op = ctx->children.at(1)->getText();
    context.diagnostic.issueError("Cannot perform operation '" + op
                                    + "' on type '" + lhsExpr->type->toString() + "' and '"
                                    + rhsExpr->type->toString() + "'", ctx);
    return (Expr*) binExpr;
  }

  assert(*lhsExpr->type == *rhsExpr->type && "Only ints here");
  return (Expr*)binExpr;
}


antlrcpp::Any TypeChecker::visitAss(LatteParser::AssContext *ctx) {
  assert(ctx->children.size() == 4);
  auto *rhs = ctx->children.at(2);
  Expr *rhsExpr = visit(rhs);
  std::string varName = ctx->children.at(0)->getText();

  if (!variableScope.findVariableType(varName)) {
    context.diagnostic.issueError("Use of undeclared variable '" + varName + "'", ctx);
    return (Type*)nullptr;
  }

  if (*variableScope.findVariableType(varName) != *rhsExpr->type) {
    context.diagnostic.issueError("Cannot assign expression of type '"
                                    + rhsExpr->type->toString()
                                    + "' to variable of type '"
                                    + variableScope.findVariableType(varName)->toString() + "'" , ctx);
    return (Type*)nullptr;
  }


  return (Stmt*)new AssignStmt(std::move(varName), rhsExpr);
}

antlrcpp::Any TypeChecker::visitProgram(LatteParser::ProgramContext *ctx) {
  // Open global scope.
  variableScope.openNewScope();
  initialPass = true;
  LatteBaseVisitor::visitProgram(ctx);

  initialPass = false;

  for (auto *children :ctx->children) {
    ast.definitions.push_back(visit(children));
  }
  //LatteBaseVisitor::visitProgram(ctx);
  variableScope.closeScope();
  return {};
}

antlrcpp::Any TypeChecker::visitFuncDef(LatteParser::FuncDefContext *ctx) {
  // type_ ID '(' arg? ')'
  std::string funName = ctx->children.at(1)->getText();


  auto *funDef = new FunctionDef;
//  functionName[ctx] = funName;

  if (initialPass) {
    auto * funType = new FunctionType;
    funType->returnType = visit(ctx->children.front());

    if (!variableScope.addVariableType(funName, funType))
      context.diagnostic.issueError("redefinition of function '" + funName + "'", ctx);

    if (ctx->children.size() == 6) {
      funDef->arguments =
          visit(ctx->children.at(3)).as<std::vector<ArgDecl>>();
      for (ArgDecl &argDecl : funDef->arguments) {
        funType->argumentTypes.push_back(argDecl.type);
      }
    }
    else {
      assert(ctx->children.size() == 5);
    }
    return {};
  }

  auto *funType = cast<FunctionType>(variableScope.findVariableTypeCurrentScope(funName));
  currentReturnType = funType->returnType;

  variableScope.openNewScope();
  // Add argument names
  if (ctx->children.size() == 6)
    visit(ctx->children.at(3));
  else
    assert(ctx->children.size() == 5);
  funDef->block = visit(ctx->children.back());



  funDef->functionType = funType;
  funDef->name = funName;
  variableScope.closeScope();
  return (Def*)funDef;
}

antlrcpp::Any TypeChecker::visitArg(LatteParser::ArgContext *ctx) {
  std::vector<ArgDecl> arguments;
  for (unsigned i = 0; i < ctx->children.size(); i += 3) {
    ArgDecl decl;
    decl.type = visit(ctx->children.at(i));
    decl.name = ctx->children.at(i + 1)->getText();
    arguments.push_back(decl);
    if (!initialPass) {
      if (!variableScope.addVariableType(decl.name, decl.type)) {
        context.diagnostic.issueError("redefinition of function '" + decl.name + "'", ctx);
      }
    }
  }
  return arguments;
}

antlrcpp::Any TypeChecker::visitEInt(LatteParser::EIntContext *ctx) {
  return (Expr*)new ConstIntExpr(getInt(), std::stoi(ctx->getText()));
}

antlrcpp::Any TypeChecker::visitEFalse(LatteParser::EFalseContext *) {
  return (Expr*) new BooleanExpr(getBool(), false);
}

antlrcpp::Any TypeChecker::visitETrue(LatteParser::ETrueContext *) {
  return (Expr*) new BooleanExpr(getBool(), true);
}

antlrcpp::Any TypeChecker::visitEStr(LatteParser::EStrContext *) {
  return getStr();
}

antlrcpp::Any TypeChecker::visitDecl(LatteParser::DeclContext *ctx) {
  assert(ctx->children.size() >= 3);

  Type *type = visit(ctx->children.at(0));
  auto *declStmt = new DeclStmt;
  declStmt->type = type;

  if (isVoid(*type)) {
    context.diagnostic.issueError(
      "Cannot initialize variable of type void", ctx);
    return {};
  }

  // Move i by 2 to skip commas.
  for (unsigned i = 1; i < ctx->children.size() - 1; i += 2) {
    auto *item = ctx->children.at(i);
    DeclItem declItem = visit(item);
    declItem.parent = declStmt;
    declStmt->decls.push_back(declItem);

    if (declItem.initializer != nullptr && *declItem.initializer->type != *type) {
      context.diagnostic.issueError(
        "Cannot initialize variable '"
          + declItem.name + "' of type '" + type->toString() +
          "' with initializer of type '" + declItem.initializer->type->toString() + "'", ctx);
    }

    if (!variableScope.addVariableType(declItem.name, type)) {
      context.diagnostic.issueError(
        "Variable '" + declItem.name + "' was already declared in this scope", ctx);
    }
  }

  return (Stmt*)declStmt;
}

antlrcpp::Any TypeChecker::visitItem(LatteParser::ItemContext *ctx) {
  assert(ctx->children.size() == 1 || ctx->children.size() == 3);
  std::string varName = ctx->children.at(0)->getText();
  if (ctx->children.size() == 3) {
    // We want to disallow stmt like:
    // int a = a;
    // To do this, we firstly unregister the variable having the same name,
    // this way if variable used on lhs was previously registered then it will
    // not find it and raise an error.
    Type * rollbackType = variableScope.temporariryUnregister(varName);
    Expr * expr = visit(ctx->children.at(2));
    variableScope.registerBack(varName, rollbackType);
    return DeclItem{varName, expr, nullptr};
  }
  return DeclItem{varName, nullptr, nullptr};
}


antlrcpp::Any TypeChecker::visitEId(LatteParser::EIdContext *ctx) {
  assert(ctx->children.size() == 1);

  auto name = ctx->children.front()->getText();
  auto *type = visitID(name, ctx);

  return (Expr*)new VarExpr(type, name);
}


Type *TypeChecker::handleIncrOrDecr(LatteParser::StmtContext *ctx, const std::string &op) {
  assert(ctx->children.size() == 3);
  Type * type = visitID(ctx->children.at(0)->getText(), ctx);
  std::string varName = ctx->children.at(0)->getText();
  if (type == nullptr)
    return type;

  if (!isIntegral(*type)) {
    context.diagnostic.issueError("Can't perform operation " + op + " on variable '"
                                    + varName + "' having type '"
                                    + type->toString() + "'", ctx);
    return getInt();
  }

  return type;
}

antlrcpp::Any TypeChecker::visitIncr(LatteParser::IncrContext *ctx) {
  return handleIncrOrDecr(ctx, "++");
}

antlrcpp::Any TypeChecker::visitDecr(LatteParser::DecrContext *ctx) {
  return handleIncrOrDecr(ctx, "--");
}

Type *TypeChecker::visitID(const std::string &varName, antlr4::ParserRuleContext *ctx) {

  if (!variableScope.findVariableType(varName)) {
    context.diagnostic.issueError("Use of undeclared variable '" + varName + "'", ctx);
    return (Type*) nullptr;
  }

  return variableScope.findVariableType(varName);
}


antlrcpp::Any TypeChecker::visitEOr(LatteParser::EOrContext *ctx) {
  return handleBinaryBooleans(ctx, BinExpr::BinOp::Or);
}

antlrcpp::Any TypeChecker::visitEAnd(LatteParser::EAndContext *ctx) {
  return handleBinaryBooleans(ctx, BinExpr::BinOp::And);
}


Expr *TypeChecker::handleBinaryBooleans(LatteParser::ExprContext *ctx,
                                        BinExpr::BinOp binOp) {
  assert(ctx->children.size() == 3);
  auto *lhs = ctx->children.at(0);
  Expr *lhsExpr = visit(lhs);
  auto *rhs = ctx->children.at(2);
  Expr* rhsExpr = visit(rhs);

  auto * binExpr = new BinExpr(getBool(), binOp, lhsExpr, rhsExpr);
  if (lhsExpr->type == nullptr || rhsExpr->type == nullptr)
    return binExpr;

  // TODO handle string
  if (!isBoolean(*lhsExpr->type) || !isBoolean(*rhsExpr->type)) {
    std::string op = ctx->children.at(1)->getText();
    context.diagnostic.issueError("Cannot perform operation '" + op
                                    + "' on type '" + lhsExpr->type->toString() + "' and '"
                                    + rhsExpr->type->toString() + "'", ctx);
    return binExpr;
  }

  assert(*lhsExpr->type == *rhsExpr->type && "Only boolean here");
  return binExpr;
}

antlrcpp::Any TypeChecker::visitEUnOp(LatteParser::EUnOpContext *ctx) {
  assert(ctx->children.size() == 2);
  Type *type = visit(ctx->children.at(1));
  auto op = ctx->children.at(0)->getText();
  if (op == "-") {
    if (!isIntegral(*type)) {
      context.diagnostic.issueError("Can't perform unary operator '-' on type '"
                                      + type->toString() + "'", ctx);
      return getInt();
    }
    return type;
  } else if (op == "!") {
    if (!isBoolean(*type)) {
      context.diagnostic.issueError("Can't perform unary operator '!' on type '"
                                      + type->toString() + "'", ctx);
      return getInt();
    }
    return type;
  }
  assert(false && "Unknown operator");
  return {};
}

antlrcpp::Any TypeChecker::visitBlock(LatteParser::BlockContext *ctx) {
  variableScope.openNewScope();
  Block block;
  assert(ctx->children.size() >= 2);
  for (unsigned i = 1; i < ctx->children.size() - 1; i++) {
    block.stmts.push_back(visit(ctx->children.at(i)));
  }
  variableScope.closeScope();
  return block;
}

antlrcpp::Any TypeChecker::visitEParen(LatteParser::EParenContext *ctx) {
  return visit(ctx->children.at(1));
}

antlrcpp::Any TypeChecker::visitEFunCall(LatteParser::EFunCallContext *ctx) {
  assert(3 <= ctx->children.size());
  std::string funName = ctx->children.front()->getText();
  Type *idType = visitID(funName, ctx);
  if (auto *funType =  dyn_cast<FunctionType>(idType)) {

    if (ctx->children.size() <= 3)
      return funType->returnType;

    auto argumentTypes = [this](auto *ctx) {
      std::vector<Type*> argumentTypes;
      for (unsigned i = 2; i < ctx->children.size(); i += 2) {
        Type *argumentType = visit(ctx->children.at(i));
        argumentTypes.push_back(argumentType);
      }
      return argumentTypes;
    }(ctx);

    if (argumentTypes.size() != funType->argumentTypes.size()) {
      context.diagnostic.issueError("Function '" + funName + "' requires "
                                        + std::to_string(funType->argumentTypes.size())
                                        + " arguments; " +
          std::to_string(argumentTypes.size()) + " was provided", ctx);
      return funType->returnType;
    }


    for (unsigned i = 0; i < argumentTypes.size(); i++) {
      if (*argumentTypes.at(i) == *funType->argumentTypes.at(i))
        continue;
      context.diagnostic.issueError("Function '" + funName + "' expects type '"
          + funType->argumentTypes.at(i)->toString() + "' as argument "
                                        + std::to_string(funType->argumentTypes.size())
                                        + "; got argument of type '"
                                        + argumentTypes.at(i)->toString() +"'"
          , ctx);
    }

    return funType->returnType;
  }

  context.diagnostic.issueError("Type '" + idType->toString() + "' can't be called", ctx);
  return idType;

}

antlrcpp::Any TypeChecker::visitRet(LatteParser::RetContext *ctx) {
  assert(ctx->children.size() == 3);
  Expr *expr = visit(ctx->children.at(1));
  if (*expr->type != *currentReturnType)
    context.diagnostic.issueError("Expected expression of type '"
                                      + currentReturnType->toString() +
        "' but got '" + expr->type->toString() + "'", ctx);
  return (Stmt*)new ReturnStmt(expr);
}

antlrcpp::Any TypeChecker::visitVRet(LatteParser::VRetContext *ctx) {
  assert(ctx->children.size() == 2);
  if (!isVoid(*currentReturnType))
    context.diagnostic.issueError("Expected expression of type '"
                                      + currentReturnType->toString() +
        "'", ctx);

  return (Stmt*)new ReturnStmt(nullptr);
}
antlrcpp::Any TypeChecker::visitCond(LatteParser::CondContext *ctx) {
  assert(ctx->children.size() == 5);

  Expr *cond = visit(ctx->children.at(2));
  if (!isBoolean(*cond->type))
    context.diagnostic.issueError("Expected boolean expr inside if", ctx);

  Stmt *stmt = visit(ctx->children.at(4));
  return (Stmt*)new IfStmt(cond, stmt, nullptr);
}

antlrcpp::Any TypeChecker::visitCondElse(LatteParser::CondElseContext *ctx) {
  assert(ctx->children.size() == 7);

  Expr *cond = visit(ctx->children.at(2));
  if (!isBoolean(*cond->type))
    context.diagnostic.issueError("Expected boolean expr inside if", ctx);

  Stmt *stmt = visit(ctx->children.at(4));
  Stmt *elseStmt = visit(ctx->children.at(6));
  return (Stmt*)new IfStmt(cond, stmt, elseStmt);
}

antlrcpp::Any TypeChecker::visitWhile(LatteParser::WhileContext *ctx) {
  assert(ctx->children.size() == 5);

  Expr *cond = visit(ctx->children.at(2));
  if (!isBoolean(*cond->type))
    context.diagnostic.issueError("Expected boolean expr inside if", ctx);

  Stmt *stmt = visit(ctx->children.at(4));
  return (Stmt*) new WhileStmt{cond, stmt};
}

antlrcpp::Any TypeChecker::visitClassName(LatteParser::ClassNameContext *ctx) {
  std::string typeName = ctx->getText();
  if (!classTypes.count(typeName)) {
    context.diagnostic.issueError("Unknown class type '" + typeName + "'", ctx);
    return (Type*)nullptr;
  }

  return (Type*)classTypes.at(typeName);
}
antlrcpp::Any TypeChecker::visitClassDef(LatteParser::ClassDefContext *ctx) {
  assert(4 <= ctx->children.size());

  auto *classType = new ClassType;
  classType->name = ctx->children.at(1)->getText();

  if (classTypes.count(classType->name)) {
    context.diagnostic.issueError(
        "Duplicated name for '" + classType->name + "'", ctx);
    return (Type*)nullptr;
  } else {
    classTypes[classType->name] = classType;
  }

  if (variableScope.findVariableType(classType->name) != nullptr) {
    context.diagnostic.issueError(
        "Duplicated name for '" + classType->name + "'", ctx);
  }

  unsigned classItemsBeg;
  if (ctx->children.at(2)->getText() == ":") {
    classItemsBeg = 5;
    std::string baseClass = ctx->children.at(3)->getText();
    if (classTypes.count(baseClass)) {
      classType->baseClass = classTypes.at(baseClass);
    } else {
      context.diagnostic.issueError("Unknown class type '" + baseClass + "'", ctx);
    }
  } else
    classItemsBeg = 3;

  for (unsigned i = classItemsBeg; i < ctx->children.size() - 1; i++) {
    // TODO
  }



  return (Type*)classType;
}
antlrcpp::Any TypeChecker::visitEmpty(LatteParser::EmptyContext *) {
  return (Stmt*)new EmptyStmt;
}
antlrcpp::Any TypeChecker::visitBlockStmt(LatteParser::BlockStmtContext *ctx) {
  auto * stmt = new BlockStmt;
  stmt->block = visit(ctx->children.front());
  return (Stmt*)stmt;
}
antlrcpp::Any TypeChecker::visitSExp(LatteParser::SExpContext *ctx) {
  Expr *expr = visit(ctx->children.front());
  return (Stmt*)new ExprStmt(expr);
}

