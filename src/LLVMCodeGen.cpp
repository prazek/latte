

#include "LLVMCodeGen.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include "llvm/IR/Verifier.h"


llvm::Value *LLVMCodeGen::visitAST(AST &ast) {

}
llvm::Value *LLVMCodeGen::visitDef(Def &def) {

}
llvm::Value *LLVMCodeGen::visitFunctionDef(FunctionDef &functionDef) {
  /*auto *astFunType = cast<FunctionType>(typeChecker.types.at(ctx));
  auto *funType = llvm::cast<llvm::FunctionType>(astFunType->toLLVMType(module->getContext()));

  llvm::Function *function  =
      llvm::Function::Create(funType,
                             llvm::Function::ExternalLinkage,typeChecker.functionName.at(ctx),
                             module.get());


  // TODO visit arguments.
  currentFunction = function;
  llvm::BasicBlock *bb = llvm::BasicBlock::Create(module->getContext(), "entry", function);
  builder.SetInsertPoint(bb);


  variableScope.openNewScope();

  visit(ctx->children.back());

  variableScope.closeScope();
  //llvm::Function *= module->getOrInsertFunction(typeChecker.functionName[ctx], funType);

  return {}; */
}
llvm::Value *LLVMCodeGen::visitClassDef(ClassDef &classDef) {
  return nullptr;
}
llvm::Value *LLVMCodeGen::visitBlock(Block &block) {

}
llvm::Value *LLVMCodeGen::visitStmt(Stmt &stmt) {

}
llvm::Value *LLVMCodeGen::visitBlockStmt(BlockStmt &blockStmt) {

}
llvm::Value *LLVMCodeGen::visitDeclStmt(DeclStmt &declStmt) {


  /*  auto *item = ctx->children.at(i);
    std::pair<std::string, llvm::Value*> var = visit(item);
    variableScope.addVariableType(var.first, var.second);*/
}
llvm::Value *LLVMCodeGen::visitDeclItem(DeclItem &declItem) {
  /*assert(ctx->children.size() == 1 || ctx->children.size() == 3);
  std::string varName = ctx->children.at(0)->getText();
  llvm::Type * Type = typeChecker.types.at(ctx)->toLLVMType(module->getContext());
  llvm::Instruction *instruction = builder.CreateAlloca(Type);

  if (ctx->children.size() == 3) {
    // TODO
    llvm::Instruction* inst = visit(ctx->children.at(2));

    return std::make_pair(varName, (llvm::Value*)inst);
  }
  return std::make_pair(varName, (llvm::Value*)instruction);*/
}
llvm::Value *LLVMCodeGen::visitAssignStmt(AssignStmt &assignStmt) {
  llvm::Value* rhs = visitExpr(*assignStmt.initializer);

  llvm::Value* var = variableScope.findVariableType(assignStmt.name);
  return builder.CreateStore(rhs, var);
}
llvm::Value *LLVMCodeGen::visitExprStmt(ExprStmt &exprStmt) {

}
llvm::Value *LLVMCodeGen::visitExpr(Expr &expr) {

}
llvm::Value *LLVMCodeGen::visitBinExpr(BinExpr &binExpr) {

}
llvm::Value *LLVMCodeGen::visitMulExpr(MulExpr &mulExpr) {

}
llvm::Value *LLVMCodeGen::visitAddExpr(AddExpr &addExpr) {
  llvm::Value *lhs = visitExpr(*addExpr.lhs);
  llvm::Value *rhs = visitExpr(*addExpr.rhs);
  return builder.CreateAdd(lhs, rhs);
}

llvm::Value *LLVMCodeGen::visitVarExpr(VarExpr &varExpr) {
  return nullptr;
}
llvm::Value *LLVMCodeGen::visitConstIntExpr(ConstIntExpr &constIntExpr) {

  return (llvm::Value*)llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(context),
                                              constIntExpr.value);
}
llvm::Value *LLVMCodeGen::visitBooleanExpr(BooleanExpr &booleanExpr) {
  return nullptr;
}
