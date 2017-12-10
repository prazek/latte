#pragma once

#include "LatteBaseVisitor.h"
#include "Type.h"
#include "Context.h"

class VariableScope {
public:
  void openNewScope() {
    varTypes.emplace_back();
  }

  void closeScope() {
    assert(!varTypes.empty());
    varTypes.pop_back();
  }

  [[nodiscard]]
  bool addVariableType(std::string name, Type *type)  {
    if (findVariableTypeCurrentScope(name))
      return false;
    varTypes.back()[std::move(name)] = type;
    return true;
  }

  // todo string_view
  Type* findVariableType(const std::string &name) const {
    for (int i = varTypes.size() - 1; i >= 0; i--) {
      const auto &map = varTypes.at(i);
      if (map.count(name))
        return map.at(name);
    }
    return nullptr;
  }

  Type *findVariableTypeCurrentScope(const std::string &name) const {
    if (varTypes.back().count(name))
      return varTypes.back().at(name);
    return nullptr;
  }

  /// Temorariy set type to nullptr
  Type *temporariryUnregister(const std::string &name) {
    for (int i = varTypes.size() - 1; i >= 0; i--) {
      auto &map = varTypes.at(i);
      if (map.count(name)) {
        Type * ret = map.at(name);
        map.at(name) = nullptr;
        return ret;
      }
    }
    return nullptr;
  }

  void registerBack(const std::string &name, Type *type) {
    if (type == nullptr)
      return;

    for (int i = varTypes.size() - 1; i >= 0; i--) {
      auto &map = varTypes.at(i);
      if (map.count(name)) {

        assert(map.at(name) == nullptr);
        map.at(name) = type;
        return;
      }
    }
    assert(false && "need to find unregistered variable");
  }

private:
  std::vector<std::unordered_map<std::string, Type*>> varTypes;
};

class TypeChecker : public LatteBaseVisitor {
private:
  Context &context;
  std::unordered_map<antlr4::ParserRuleContext *, Type*> types;
  VariableScope variableScope;
  bool initialPass;
  Type *currentReturnType;

public:
  TypeChecker(Context &context) : context(context) {}

  antlrcpp::Any visitProgram(LatteParser::ProgramContext *ctx) override;

  antlrcpp::Any visitTopDef(LatteParser::TopDefContext *ctx) override;

  antlrcpp::Any visitArg(LatteParser::ArgContext *ctx) override;

  antlrcpp::Any visitBlock(LatteParser::BlockContext *ctx) override;

  antlrcpp::Any visitDecl(LatteParser::DeclContext *ctx) override;

  antlrcpp::Any visitAss(LatteParser::AssContext *ctx) override;

  antlrcpp::Any visitIncr(LatteParser::IncrContext *ctx) override;

  antlrcpp::Any visitDecr(LatteParser::DecrContext *ctx) override;

  antlrcpp::Any visitRet(LatteParser::RetContext *ctx) override;

  antlrcpp::Any visitVRet(LatteParser::VRetContext *ctx) override;

  antlrcpp::Any visitCond(LatteParser::CondContext *ctx) override;

  antlrcpp::Any visitCondElse(LatteParser::CondElseContext *ctx) override;

  antlrcpp::Any visitWhile(LatteParser::WhileContext *ctx) override;

  antlrcpp::Any visitInt(LatteParser::IntContext *ctx) override;

  antlrcpp::Any visitStr(LatteParser::StrContext *ctx) override;

  antlrcpp::Any visitBool(LatteParser::BoolContext *ctx) override;

  antlrcpp::Any visitVoid(LatteParser::VoidContext *ctx) override;

  antlrcpp::Any visitItem(LatteParser::ItemContext *ctx) override;

  antlrcpp::Any visitEId(LatteParser::EIdContext *ctx) override;

  antlrcpp::Any visitEFunCall(LatteParser::EFunCallContext *ctx) override;

  antlrcpp::Any visitERelOp(LatteParser::ERelOpContext *ctx) override;

  antlrcpp::Any visitETrue(LatteParser::ETrueContext *ctx) override;

  antlrcpp::Any visitEOr(LatteParser::EOrContext *ctx) override;

  antlrcpp::Any visitEInt(LatteParser::EIntContext *ctx) override;

  antlrcpp::Any visitEUnOp(LatteParser::EUnOpContext *ctx) override;

  antlrcpp::Any visitEStr(LatteParser::EStrContext *ctx) override;

  antlrcpp::Any visitEMulOp(LatteParser::EMulOpContext *ctx) override;

  antlrcpp::Any visitEAnd(LatteParser::EAndContext *ctx) override;

  antlrcpp::Any visitEParen(LatteParser::EParenContext *ctx) override;

  antlrcpp::Any visitEFalse(LatteParser::EFalseContext *ctx) override;

  antlrcpp::Any visitEAddOp(LatteParser::EAddOpContext *ctx) override;

  Type *handleBinaryBooleans(LatteParser::ExprContext *ctx);
  Type *handleIncrOrDecr(LatteParser::StmtContext *ctx, const std::string &op);
  Type* visitID(const std::string& varName, antlr4::ParserRuleContext *ctx);
};


