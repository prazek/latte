
#include "TypeChecker.h"
#include "Type.h"
#include "Utilities.h"
#include <memory>

antlrcpp::Any TypeChecker::visitBool(LatteParser::BoolContext *) {
  return (Type*)new SimpleType{SimpleType::POD::Bool};
}
antlrcpp::Any TypeChecker::visitVoid(LatteParser::VoidContext *) {
  return (Type*)new SimpleType{SimpleType::POD::Void};
}
antlrcpp::Any TypeChecker::visitInt(LatteParser::IntContext *) {
  return (Type*)new SimpleType{SimpleType::POD::Int};
}
antlrcpp::Any TypeChecker::visitStr(LatteParser::StrContext *) {
  return (Type*)new SimpleType{SimpleType::POD::String};
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
    return (Type*) nullptr;
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
    // TODO type
    return (Type*)new SimpleType{SimpleType::POD::Int};
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
    return (Type*) nullptr;
  }

  assert(*lhsType == *rhsType && "Only ints here");

  auto * retType = new SimpleType{SimpleType::POD::Bool};

  types[ctx] = retType;
  return retType;
}


antlrcpp::Any TypeChecker::visitAss(LatteParser::AssContext *ctx) {
  assert(ctx->children.size() == 4);
  auto *rhs = ctx->children.at(2);
  Type *rhsType = visit(rhs);
  std::string varName = ctx->children.at(0)->getText();

  // TODO handle shadowing.

  if (!varTypes.count(varName)) {
    context.diagnostic.issueError("Use of undeclared variable '" + varName + "'", ctx);
    return (Type*)nullptr;
  }

  if (*varTypes.at(varName) != *rhsType) {
    context.diagnostic.issueError("Cannot assign expression of type '"
                                    + rhsType->toString()
                                    + "' to variable of type '"
                                    + varTypes[varName]->toString() + "'" , ctx);
    return (Type*)nullptr;
  }

  types[ctx] = rhsType;
  return rhsType;
}
antlrcpp::Any TypeChecker::visitProgram(LatteParser::ProgramContext *ctx) {
  return LatteBaseVisitor::visitProgram(ctx);
}
antlrcpp::Any TypeChecker::visitTopDef(LatteParser::TopDefContext *ctx) {
  return LatteBaseVisitor::visitTopDef(ctx);
}
antlrcpp::Any TypeChecker::visitArg(LatteParser::ArgContext *ctx) {
  return LatteBaseVisitor::visitArg(ctx);
}
antlrcpp::Any TypeChecker::visitEInt(LatteParser::EIntContext *) {
  return (Type*)new SimpleType{SimpleType::POD::Int};
}
antlrcpp::Any TypeChecker::visitEFalse(LatteParser::EFalseContext *) {
  return (Type*)new SimpleType{SimpleType::POD::Bool};
}
antlrcpp::Any TypeChecker::visitETrue(LatteParser::ETrueContext *) {
  return (Type*)new SimpleType{SimpleType::POD::Bool};
}
antlrcpp::Any TypeChecker::visitEStr(LatteParser::EStrContext *ctx) {
  return (Type*)new SimpleType{SimpleType::POD::String};
}

antlrcpp::Any TypeChecker::visitDecl(LatteParser::DeclContext *ctx) {
  assert(ctx->children.size() >= 3);
  Type *type = visit(ctx->children.at(0));
  // Move i by 2 to skip commas.
  for (unsigned i = 1; i < ctx->children.size() - 1; i += 2) {
    auto *item = ctx->children.at(i);
    std::pair<std::string, Type*> var = visit(item);
    if (var.second != nullptr && *var.second != *type) {
      context.diagnostic.issueError(
        "Cannot initialize variable '"
          + var.first + "' of type '" + type->toString() +
          "' with initializer of type '" + var.second->toString() + "'",
        ctx
      );
    }
    varTypes[var.first] = type;
  }
  types[ctx] = type;
  return type;
}

antlrcpp::Any TypeChecker::visitItem(LatteParser::ItemContext *ctx) {
  assert(ctx->children.size() == 1 || ctx->children.size() == 3);
  std::string varName = ctx->getText();
  if (ctx->children.size() == 3) {
    Type * type = visit(ctx->children.at(2));
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
    return nullptr;
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
  if (!varTypes.count(varName)) {
    context.diagnostic.issueError("Use of undeclared variable '" + varName + "'", ctx);
    return (Type*) nullptr;
  }

  return varTypes.at(varName);
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

