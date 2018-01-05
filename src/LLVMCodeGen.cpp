

#include "LLVMCodeGen.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include "llvm/IR/Verifier.h"

//using namespace llvm;


antlrcpp::Any LLVMCodeGen::visitProgram(LatteParser::ProgramContext *ctx) {
  return LatteBaseVisitor::visitProgram(ctx);
}
antlrcpp::Any LLVMCodeGen::visitFuncDef(LatteParser::FuncDefContext *ctx) {
  //FunctionType *ft = TypeBuilder<types::i<8>(types::i<32>*), true>::get();

  auto *astFunType = cast<FunctionType>(typeChecker.types.at(ctx));
  auto *funType = llvm::cast<llvm::FunctionType>(astFunType->toLLVMType(module->getContext()));

  llvm::Function *function  =
      llvm::Function::Create(funType,
                             llvm::Function::ExternalLinkage,typeChecker.functionName.at(ctx),
                             module.get());


  // TODO visit arguments.
  currentFunction = function;
  llvm::BasicBlock *bb = llvm::BasicBlock::Create(module->getContext(), "entry", function);

  builder.SetInsertPoint(bb);

  visit(ctx->children.back());

  //llvm::Function *= module->getOrInsertFunction(typeChecker.functionName[ctx], funType);

  return {};
}

antlrcpp::Any LLVMCodeGen::visitClassDef(LatteParser::ClassDefContext *ctx) {
  return LatteBaseVisitor::visitClassDef(ctx);
}
antlrcpp::Any LLVMCodeGen::visitItemVarDecl(LatteParser::ItemVarDeclContext *ctx) {
  return LatteBaseVisitor::visitItemVarDecl(ctx);
}
antlrcpp::Any LLVMCodeGen::visitItemMethodDef(LatteParser::ItemMethodDefContext *ctx) {
  return LatteBaseVisitor::visitItemMethodDef(ctx);
}
antlrcpp::Any LLVMCodeGen::visitArg(LatteParser::ArgContext *ctx) {
  return LatteBaseVisitor::visitArg(ctx);
}
antlrcpp::Any LLVMCodeGen::visitBlock(LatteParser::BlockContext *ctx) {
  return LatteBaseVisitor::visitBlock(ctx);
}
antlrcpp::Any LLVMCodeGen::visitEmpty(LatteParser::EmptyContext *ctx) {
  return LatteBaseVisitor::visitEmpty(ctx);
}
antlrcpp::Any LLVMCodeGen::visitBlockStmt(LatteParser::BlockStmtContext *ctx) {
  return LatteBaseVisitor::visitBlockStmt(ctx);
}
antlrcpp::Any LLVMCodeGen::visitDecl(LatteParser::DeclContext *ctx) {

  llvm::Type * Type = typeChecker.types.at(ctx)->toLLVMType(module->getContext());
  llvm::Instruction *instruction = builder.CreateAlloca(Type);




}
antlrcpp::Any LLVMCodeGen::visitAss(LatteParser::AssContext *ctx) {
  return LatteBaseVisitor::visitAss(ctx);
}
antlrcpp::Any LLVMCodeGen::visitIncr(LatteParser::IncrContext *ctx) {
  return LatteBaseVisitor::visitIncr(ctx);
}
antlrcpp::Any LLVMCodeGen::visitDecr(LatteParser::DecrContext *ctx) {
  return LatteBaseVisitor::visitDecr(ctx);
}
antlrcpp::Any LLVMCodeGen::visitRet(LatteParser::RetContext *ctx) {
  return LatteBaseVisitor::visitRet(ctx);
}
antlrcpp::Any LLVMCodeGen::visitVRet(LatteParser::VRetContext *ctx) {
  return LatteBaseVisitor::visitVRet(ctx);
}
antlrcpp::Any LLVMCodeGen::visitCond(LatteParser::CondContext *ctx) {
  return LatteBaseVisitor::visitCond(ctx);
}
antlrcpp::Any LLVMCodeGen::visitCondElse(LatteParser::CondElseContext *ctx) {
  return LatteBaseVisitor::visitCondElse(ctx);
}
antlrcpp::Any LLVMCodeGen::visitWhile(LatteParser::WhileContext *ctx) {
  return LatteBaseVisitor::visitWhile(ctx);
}
antlrcpp::Any LLVMCodeGen::visitSExp(LatteParser::SExpContext *ctx) {
  return LatteBaseVisitor::visitSExp(ctx);
}
antlrcpp::Any LLVMCodeGen::visitInt(LatteParser::IntContext *ctx) {
  return LatteBaseVisitor::visitInt(ctx);
}
antlrcpp::Any LLVMCodeGen::visitStr(LatteParser::StrContext *ctx) {
  return LatteBaseVisitor::visitStr(ctx);
}
antlrcpp::Any LLVMCodeGen::visitBool(LatteParser::BoolContext *ctx) {
  return LatteBaseVisitor::visitBool(ctx);
}
antlrcpp::Any LLVMCodeGen::visitVoid(LatteParser::VoidContext *ctx) {
  return LatteBaseVisitor::visitVoid(ctx);
}
antlrcpp::Any LLVMCodeGen::visitClassName(LatteParser::ClassNameContext *ctx) {
  return LatteBaseVisitor::visitClassName(ctx);
}
antlrcpp::Any LLVMCodeGen::visitItem(LatteParser::ItemContext *ctx) {
  return LatteBaseVisitor::visitItem(ctx);
}
antlrcpp::Any LLVMCodeGen::visitEId(LatteParser::EIdContext *ctx) {
  return LatteBaseVisitor::visitEId(ctx);
}
antlrcpp::Any LLVMCodeGen::visitEFunCall(LatteParser::EFunCallContext *ctx) {
  return LatteBaseVisitor::visitEFunCall(ctx);
}
antlrcpp::Any LLVMCodeGen::visitERelOp(LatteParser::ERelOpContext *ctx) {
  return LatteBaseVisitor::visitERelOp(ctx);
}
antlrcpp::Any LLVMCodeGen::visitETrue(LatteParser::ETrueContext *ctx) {
  return LatteBaseVisitor::visitETrue(ctx);
}
antlrcpp::Any LLVMCodeGen::visitEOr(LatteParser::EOrContext *ctx) {
  return LatteBaseVisitor::visitEOr(ctx);
}
antlrcpp::Any LLVMCodeGen::visitEInt(LatteParser::EIntContext *ctx) {
  return LatteBaseVisitor::visitEInt(ctx);
}
antlrcpp::Any LLVMCodeGen::visitEMemberExpr(LatteParser::EMemberExprContext *ctx) {
  return LatteBaseVisitor::visitEMemberExpr(ctx);
}
antlrcpp::Any LLVMCodeGen::visitEUnOp(LatteParser::EUnOpContext *ctx) {
  return LatteBaseVisitor::visitEUnOp(ctx);
}
antlrcpp::Any LLVMCodeGen::visitEStr(LatteParser::EStrContext *ctx) {
  return LatteBaseVisitor::visitEStr(ctx);
}
antlrcpp::Any LLVMCodeGen::visitEMulOp(LatteParser::EMulOpContext *ctx) {
  return LatteBaseVisitor::visitEMulOp(ctx);
}
antlrcpp::Any LLVMCodeGen::visitEAnd(LatteParser::EAndContext *ctx) {
  return LatteBaseVisitor::visitEAnd(ctx);
}
antlrcpp::Any LLVMCodeGen::visitEParen(LatteParser::EParenContext *ctx) {
  return LatteBaseVisitor::visitEParen(ctx);
}
antlrcpp::Any LLVMCodeGen::visitEFalse(LatteParser::EFalseContext *ctx) {
  return LatteBaseVisitor::visitEFalse(ctx);
}
antlrcpp::Any LLVMCodeGen::visitEAddOp(LatteParser::EAddOpContext *ctx) {
  return LatteBaseVisitor::visitEAddOp(ctx);
}
antlrcpp::Any LLVMCodeGen::visitMemExpr(LatteParser::MemExprContext *ctx) {
  return LatteBaseVisitor::visitMemExpr(ctx);
}
antlrcpp::Any LLVMCodeGen::visitMemCallrBasic(LatteParser::MemCallrBasicContext *ctx) {
  return LatteBaseVisitor::visitMemCallrBasic(ctx);
}
antlrcpp::Any LLVMCodeGen::visitMemCallr(LatteParser::MemCallrContext *ctx) {
  return LatteBaseVisitor::visitMemCallr(ctx);
}
antlrcpp::Any LLVMCodeGen::visitMemVar(LatteParser::MemVarContext *ctx) {
  return LatteBaseVisitor::visitMemVar(ctx);
}
antlrcpp::Any LLVMCodeGen::visitAddOp(LatteParser::AddOpContext *ctx) {
  return LatteBaseVisitor::visitAddOp(ctx);
}
antlrcpp::Any LLVMCodeGen::visitMulOp(LatteParser::MulOpContext *ctx) {
  return LatteBaseVisitor::visitMulOp(ctx);
}
antlrcpp::Any LLVMCodeGen::visitRelOp(LatteParser::RelOpContext *ctx) {
  return LatteBaseVisitor::visitRelOp(ctx);
}
