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
                             llvm::Function::InternalLinkage, functionDef.name,
                             &module);

  assert(functionDef.arguments.size() == function->arg_size());
  int i = 0;
  for (auto &arg : function->args()) {
    auto *varDecl = functionDef.arguments.at(i++);
    arg.setName(varDecl->name);
  }

}
void LLVMCodeGenPrepare::visitClassDef(ClassDef &) {}
void LLVMCodeGenPrepare::visitDeclStmt(DeclStmt &) {}
void LLVMCodeGenPrepare::visitIncrStmt(IncrStmt &) {}
void LLVMCodeGenPrepare::visitDecrStmt(DecrStmt &) {}
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