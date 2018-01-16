#pragma once

#include "LatteBaseVisitor.h"
#include "Type.h"
#include "Context.h"
#include "VariableScope.h"
#include "AST.h"

class TypeChecker : public LatteBaseVisitor {
private:
  Context &context;

  VariableScope<Def*> variableScope;
  std::unordered_map<std::string, ClassDef*> classes;
  enum Passes {
    registerClassesNames,
    registerFunctionPrototypes,
    parseClassesWithMethodesPrototypes,
    parseFuncsAndMethods
  };
  Passes currentPass;
  Type *currentReturnType;
public:

  AST ast;
public:
  TypeChecker(Context &context) : context(context) {}

  antlrcpp::Any visitProgram(LatteParser::ProgramContext *ctx) override;
  antlrcpp::Any visitFuncDef(LatteParser::FuncDefContext *ctx) override;
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
  antlrcpp::Any visitClassName(LatteParser::ClassNameContext *ctx) override;
  antlrcpp::Any visitClassDef(LatteParser::ClassDefContext *ctx) override;
  antlrcpp::Any visitEmpty(LatteParser::EmptyContext *ctx) override;
  antlrcpp::Any visitBlockStmt(LatteParser::BlockStmtContext *ctx) override;
  antlrcpp::Any visitSExp(LatteParser::SExpContext *ctx) override;
  antlrcpp::Any visitEMemberExpr(LatteParser::EMemberExprContext *ctx) override;
  antlrcpp::Any visitFieldDecl(LatteParser::FieldDeclContext *ctx) override;
  antlrcpp::Any visitENewExpr(LatteParser::ENewExprContext *ctx) override;
  antlrcpp::Any visitEClassCast(LatteParser::EClassCastContext *ctx) override;

private:
  Expr *handleBinaryBooleans(LatteParser::ExprContext *ctx, BinExpr::BinOp);
  Stmt *handleIncrOrDecr(LatteParser::StmtContext *ctx, const std::string &op);
};


