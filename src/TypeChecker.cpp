
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
  Type *lhsType = visit(lhs);
  auto *rhs = ctx->children.at(2);
  Type* rhsType = visit(rhs);

  if (lhsType == nullptr || rhsType == nullptr)
      return (Type*) nullptr;

  if (!isIntegral(*lhsType) || !isIntegral(*rhsType)) {
    std::string op = ctx->children.at(1)->getText();
    context.diagnostic.issueError("Cannot perform operation '" + op
                                    + "' on type '" + lhsType->toString() + "' and '"
                                    + rhsType->toString() + "'", ctx);
    return getInt();
  }

  assert(*lhsType == *rhsType && "Only ints here");

  types[ctx] = lhsType;
  return lhsType;
}

antlrcpp::Any TypeChecker::visitEAddOp(LatteParser::EAddOpContext *ctx) {
  // TODO handle strings concat?
  assert(ctx->children.size() == 3);
  auto *lhs = ctx->children.at(0);
  Type *lhsType = visit(lhs);
  auto *rhs = ctx->children.at(2);
  Type* rhsType = visit(rhs);

  if (lhsType == nullptr || rhsType == nullptr)
    return (Type*) nullptr;

  if (!isIntegral(*lhsType) || !isIntegral(*rhsType)) {
    std::string op = ctx->children.at(1)->getText();
    context.diagnostic.issueError("Cannot perform operation '" + op
                                    + "' on type '" + lhsType->toString() + "' and '"
                                    + rhsType->toString() + "'", ctx);
    return getInt();
  }

  assert(*lhsType == *rhsType && "Only ints here");

  types[ctx] = lhsType;
  return lhsType;
}

antlrcpp::Any TypeChecker::visitERelOp(LatteParser::ERelOpContext *ctx) {
  assert(ctx->children.size() == 3);
  auto *lhs = ctx->children.at(0);
  Type *lhsType = visit(lhs);
  auto *rhs = ctx->children.at(2);
  Type* rhsType = visit(rhs);

  if (lhsType == nullptr || rhsType == nullptr)
    return (Type*) nullptr;

  // TODO handle string
  if (!isIntegral(*lhsType) || !isIntegral(*rhsType)) {
    std::string op = ctx->children.at(1)->getText();
    context.diagnostic.issueError("Cannot perform operation '" + op
                                    + "' on type '" + lhsType->toString() + "' and '"
                                    + rhsType->toString() + "'", ctx);
    return getBool();
  }

  assert(*lhsType == *rhsType && "Only ints here");

  auto * retType = getBool();

  types[ctx] = retType;
  return retType;
}


antlrcpp::Any TypeChecker::visitAss(LatteParser::AssContext *ctx) {
  assert(ctx->children.size() == 4);
  auto *rhs = ctx->children.at(2);
  Type *rhsType = visit(rhs);
  std::string varName = ctx->children.at(0)->getText();

  if (!variableScope.findVariableType(varName)) {
    context.diagnostic.issueError("Use of undeclared variable '" + varName + "'", ctx);
    return (Type*)nullptr;
  }

  if (*variableScope.findVariableType(varName) != *rhsType) {
    context.diagnostic.issueError("Cannot assign expression of type '"
                                    + rhsType->toString()
                                    + "' to variable of type '"
                                    + variableScope.findVariableType(varName)->toString() + "'" , ctx);
    return (Type*)nullptr;
  }

  types[ctx] = rhsType;
  return rhsType;
}

antlrcpp::Any TypeChecker::visitProgram(LatteParser::ProgramContext *ctx) {
  // Open global scope.
  variableScope.openNewScope();
  initialPass = true;
  LatteBaseVisitor::visitProgram(ctx);

  initialPass = false;
  LatteBaseVisitor::visitProgram(ctx);
  variableScope.closeScope();
  return {};
}

antlrcpp::Any TypeChecker::visitTopDef(LatteParser::TopDefContext *ctx) {
  // type_ ID '(' arg? ')'
  std::string funName = ctx->children.at(1)->getText();

  if (initialPass) {
    auto * funType = new FunctionType;
    funType->returnType = visit(ctx->children.front());

    f

    if (variableScope.addVariableType(funName, funType))
      context.diagnostic.issueError("redefinition of function '" + funName + "'", ctx);
    return {};
  }

  auto *funType = cast<FunctionType>(variableScope.findVariableTypeCurrentScope(funName));
  currentReturnType = funType->returnType;

  return visit(ctx->children.back());
}

antlrcpp::Any TypeChecker::visitArg(LatteParser::ArgContext *ctx) {
  std::vector<Type*>
  for (unsigned i = 3; i < ctx->children.size() - 2; i += 2)
    funType->argumentTypes.push_back((Type*)visit(ctx->children.at(i)));
  return LatteBaseVisitor::visitArg(ctx);
}

antlrcpp::Any TypeChecker::visitEInt(LatteParser::EIntContext *) {
  return getInt();
}

antlrcpp::Any TypeChecker::visitEFalse(LatteParser::EFalseContext *) {
  return getBool();
}

antlrcpp::Any TypeChecker::visitETrue(LatteParser::ETrueContext *) {
  return getBool();
}

antlrcpp::Any TypeChecker::visitEStr(LatteParser::EStrContext *) {
  return getStr();
}

antlrcpp::Any TypeChecker::visitDecl(LatteParser::DeclContext *ctx) {
  assert(ctx->children.size() >= 3);
  Type *type = visit(ctx->children.at(0));
  if (isVoid(*type)) {
    context.diagnostic.issueError(
      "Cannot initialize variable of type void", ctx);
    return {};
  }

  // Move i by 2 to skip commas.
  for (unsigned i = 1; i < ctx->children.size() - 1; i += 2) {
    auto *item = ctx->children.at(i);
    std::pair<std::string, Type*> var = visit(item);

    if (var.second != nullptr && *var.second != *type) {
      context.diagnostic.issueError(
        "Cannot initialize variable '"
          + var.first + "' of type '" + type->toString() +
          "' with initializer of type '" + var.second->toString() + "'", ctx);
    }

    if (!variableScope.addVariableType(var.first, type)) {
      context.diagnostic.issueError(
        "Variable '" + var.first + "' was already declared in this scope", ctx);
    }
  }
  types[ctx] = type;
  return type;
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
    Type * type = visit(ctx->children.at(2));
    variableScope.registerBack(varName, rollbackType);
    return std::make_pair(varName, type);
  }
  return std::make_pair(varName, (Type*)nullptr);
}
antlrcpp::Any TypeChecker::visitEId(LatteParser::EIdContext *ctx) {
  assert(ctx->children.size() == 1);
  return visitID(ctx->children.at(0)->getText(), ctx);
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
  return handleBinaryBooleans(ctx);
}

antlrcpp::Any TypeChecker::visitEAnd(LatteParser::EAndContext *ctx) {
  return handleBinaryBooleans(ctx);
}


Type *TypeChecker::handleBinaryBooleans(LatteParser::ExprContext *ctx) {
  assert(ctx->children.size() == 3);
  auto *lhs = ctx->children.at(0);
  Type *lhsType = visit(lhs);
  auto *rhs = ctx->children.at(2);
  Type* rhsType = visit(rhs);

  if (lhsType == nullptr || rhsType == nullptr)
    return (Type*) nullptr;

  // TODO handle string
  if (!isBoolean(*lhsType) || !isBoolean(*rhsType)) {
    std::string op = ctx->children.at(1)->getText();
    context.diagnostic.issueError("Cannot perform operation '" + op
                                    + "' on type '" + lhsType->toString() + "' and '"
                                    + rhsType->toString() + "'", ctx);
    return (Type*) nullptr;
  }

  assert(*lhsType == *rhsType && "Only boolean here");
  types[ctx] = lhsType;
  return lhsType;
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
  LatteBaseVisitor::visitBlock(ctx);
  variableScope.closeScope();
  return {};
}

antlrcpp::Any TypeChecker::visitEParen(LatteParser::EParenContext *ctx) {
  return visit(ctx->children.at(1));
}
antlrcpp::Any TypeChecker::visitEFunCall(LatteParser::EFunCallContext *ctx) {

  return LatteBaseVisitor::visitEFunCall(ctx);
}

