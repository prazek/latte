#include "LLVMCodeGenPrepare.h"
#include "BuiltinFunctions.h"


void LLVMCodeGenPrepare::visitAST(AST &ast) {
  for (FunctionDef * functionDef : BuiltinFunctions::getBuiltinFunctions()) {
    auto *funType = llvm::cast<llvm::FunctionType>(functionDef->getFunType()->toLLVMType(module.getContext()));
    llvm::Function::Create(funType,
                           llvm::Function::ExternalLinkage, functionDef->name,
                           &module);
  }
  ASTVisitor::visitAST(ast);
}


void LLVMCodeGenPrepare::visitFunctionDef(FunctionDef &functionDef) {
  auto *funType = llvm::cast<llvm::FunctionType>(functionDef.getFunType()->toLLVMType(module.getContext()));
  llvm::Function *function  =
      llvm::Function::Create(funType,
                             llvm::Function::ExternalLinkage, functionDef.name,
                             &module);

  assert(functionDef.arguments.size() == function->arg_size());
  int i = 0;
  for (auto &arg : function->args()) {
    auto *varDecl = functionDef.arguments.at(i++);
    arg.setName(varDecl->name);
  }
  visitBlock(functionDef.block);
  Stmt *lastStmt = nullptr;
  if (!functionDef.block.stmts.empty())
    lastStmt = functionDef.block.stmts.back();

  if (lastStmt && (isa<ReturnStmt>(lastStmt) || isa<UnreachableStmt>(lastStmt)))
    return;

  // Add implicit return void
  if (SimpleType::isVoid(*functionDef.getFunType()->returnType))
    functionDef.block.stmts.push_back(new ReturnStmt(nullptr));
  else // Add unreachable
    functionDef.block.stmts.push_back(new UnreachableStmt);

  //visitBlock(functionDef.block);
}

void LLVMCodeGenPrepare::visitClassDef(ClassDef &) {}
void LLVMCodeGenPrepare::visitDeclStmt(DeclStmt &) {}
void LLVMCodeGenPrepare::visitIncrStmt(IncrStmt &) {}
void LLVMCodeGenPrepare::visitDecrStmt(DecrStmt &) {}
void LLVMCodeGenPrepare::visitUnreachableStmt(UnreachableStmt &) {}
void LLVMCodeGenPrepare::visitReturnStmt(ReturnStmt &) {}
void LLVMCodeGenPrepare::visitIfStmt(IfStmt &) {}
void LLVMCodeGenPrepare::visitWhileStmt(WhileStmt &) {}
void LLVMCodeGenPrepare::visitUnaryExpr(UnaryExpr &) {}
void LLVMCodeGenPrepare::visitBinExpr(BinExpr &) {}
void LLVMCodeGenPrepare::visitVarExpr(VarExpr &) {}
void LLVMCodeGenPrepare::visitConstIntExpr(ConstIntExpr &) {}
void LLVMCodeGenPrepare::visitBooleanExpr(BooleanExpr &) {}
void LLVMCodeGenPrepare::visitCallExpr(CallExpr &) {}
void LLVMCodeGenPrepare::visitConstStringExpr(ConstStringExpr &) {}
void LLVMCodeGenPrepare::visitRValueImplicitCast(RValueImplicitCast &) {}
void LLVMCodeGenPrepare::visitFunExpr(FunExpr &funExpr) {}
