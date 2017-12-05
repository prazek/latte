#pragma once

#include "LatteBaseVisitor.h"
#include "Type.h"
#include "Context.h"
class TypeChecker : public LatteBaseVisitor {
private:

  Context &context;
  std::unordered_map<antlr4::ParserRuleContext *, Type*> types;
  std::unordered_map<std::string, Type*> varTypes;
public:
  TypeChecker(Context &context) : context(context) {}

  antlrcpp::Any visitProgram(LatteParser::ProgramContext *ctx) override;

  antlrcpp::Any visitTopDef(LatteParser::TopDefContext *ctx) override;

  antlrcpp::Any visitArg(LatteParser::ArgContext *ctx) override;
/*
  antlrcpp::Any visitBlock(LatteParser::BlockContext *ctx) override;

  antlrcpp::Any visitEmpty(LatteParser::EmptyContext *ctx) override;

  antlrcpp::Any visitBlockStmt(LatteParser::BlockStmtContext *ctx) override;
*/
  antlrcpp::Any visitDecl(LatteParser::DeclContext *ctx) override;

  antlrcpp::Any visitAss(LatteParser::AssContext *ctx) override;

  antlrcpp::Any visitIncr(LatteParser::IncrContext *ctx) override;

  antlrcpp::Any visitDecr(LatteParser::DecrContext *ctx) override;
/*
  antlrcpp::Any visitRet(LatteParser::RetContext *ctx) override;

  antlrcpp::Any visitVRet(LatteParser::VRetContext *ctx) override;

  antlrcpp::Any visitCond(LatteParser::CondContext *ctx) override;

  antlrcpp::Any visitCondElse(LatteParser::CondElseContext *ctx) override;

  antlrcpp::Any visitWhile(LatteParser::WhileContext *ctx) override;

  antlrcpp::Any visitSExp(LatteParser::SExpContext *ctx) override;
*/
  antlrcpp::Any visitInt(LatteParser::IntContext *ctx) override;

  antlrcpp::Any visitStr(LatteParser::StrContext *ctx) override;

  antlrcpp::Any visitBool(LatteParser::BoolContext *ctx) override;

  antlrcpp::Any visitVoid(LatteParser::VoidContext *ctx) override;

  antlrcpp::Any visitItem(LatteParser::ItemContext *ctx) override;

  antlrcpp::Any visitEId(LatteParser::EIdContext *ctx) override;
/*
  antlrcpp::Any visitEFunCall(LatteParser::EFunCallContext *ctx) override;
*/
  antlrcpp::Any visitERelOp(LatteParser::ERelOpContext *ctx) override;

  antlrcpp::Any visitETrue(LatteParser::ETrueContext *ctx) override;

  antlrcpp::Any visitEOr(LatteParser::EOrContext *ctx) override;

  antlrcpp::Any visitEInt(LatteParser::EIntContext *ctx) override;
/*
  antlrcpp::Any visitEUnOp(LatteParser::EUnOpContext *ctx) override;
*/
  antlrcpp::Any visitEStr(LatteParser::EStrContext *ctx) override;

  antlrcpp::Any visitEMulOp(LatteParser::EMulOpContext *ctx) override;

  antlrcpp::Any visitEAnd(LatteParser::EAndContext *ctx) override;
/*
  antlrcpp::Any visitEParen(LatteParser::EParenContext *ctx) override;
*/
  antlrcpp::Any visitEFalse(LatteParser::EFalseContext *ctx) override;

  antlrcpp::Any visitEAddOp(LatteParser::EAddOpContext *ctx) override;

  Type *handleBinaryBooleans(LatteParser::ExprContext *ctx);
  Type *handleIncrOrDecr(LatteParser::StmtContext *ctx, const std::string &op);
  Type* visitID(const std::string& varName, antlr4::ParserRuleContext *ctx);
};


