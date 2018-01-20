#include "LLVMCodeGenPrepare.h"
#include "BuiltinFunctions.h"
#include "LLVMClassCodeGen.h"


static void registerMalloc(llvm::Module &module) {
  //i8* @malloc(i64 %6)
  auto *funType = llvm::FunctionType::get(
      llvm::IntegerType::getInt8PtrTy(module.getContext()),
      {llvm::IntegerType::getInt64Ty(module.getContext())},
      false);

  llvm::Function::Create(funType,
                         llvm::Function::ExternalLinkage, "malloc",
                         &module);
}

void LLVMCodeGenPrepare::visitAST(AST &ast) {
  registerMalloc(module);
  for (FunctionDef * functionDef : BuiltinFunctions::getBuiltinFunctions()) {
    auto *funType = llvm::cast<llvm::FunctionType>(functionDef->getFunType()->toLLVMType(module));
    llvm::Function::Create(funType,
                           llvm::Function::ExternalLinkage, functionDef->name,
                           &module);
  }

  std::vector<Def*> ctorsDefs;
  for (Def * def : ast.definitions) {
    if (auto *classDef = dyn_cast<ClassDef>(def)) {
      // Register class names
      llvm::StructType::create(module.getContext(), classDef->className);
      ctorsDefs.push_back(createConstructor(*classDef));
    }
  }
  // Add constructors.
  ast.definitions.insert(ast.definitions.end(),
                         std::move_iterator(ctorsDefs.begin()),
                         std::move_iterator(ctorsDefs.end()));


  ASTVisitor::visitAST(ast);

  for (Def *def :ast.definitions) {
    if (auto *classDef = dyn_cast<ClassDef>(def)) {
      emitNewOperator(module, *classDef);
    }
  }
}


void LLVMCodeGenPrepare::visitFunctionDef(FunctionDef &functionDef) {
  createFunction(functionDef, functionDef.name);

}

void LLVMCodeGenPrepare::createFunction(FunctionDef &functionDef,
                                        const std::string &functionName) {
  auto *funType = llvm::cast<llvm::FunctionType>(functionDef.getFunType()->toLLVMType(
      module));
  llvm::Function *function  =
      llvm::Function::Create(funType,
                             llvm::GlobalValue::ExternalLinkage, functionName,
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
}

void LLVMCodeGenPrepare::visitClassDef(ClassDef &def) {
  llvm::StructType *type = module.getTypeByName(def.className);

  llvm::SmallVector<llvm::Type*, 4> fieldTypes;
  fieldTypes.reserve(def.fieldDecls.size());

  for (FieldDecl *field : def.fieldDecls)
    fieldTypes.push_back(field->type->toLLVMType(module));
  type->setBody(fieldTypes);

  for (FunctionDef *method : def.methodDecls) {
    method->name = mangleMethodName(def.className, method->name);
    method->arguments.insert(method->arguments.begin(), method->thisPtr);
    method->getFunType()->argumentTypes.insert(
        method->getFunType()->argumentTypes.begin(), method->thisPtr->type);

    createFunction(*method, method->name);
  }
}

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
void LLVMCodeGenPrepare::visitFunExpr(FunExpr &) {}
void LLVMCodeGenPrepare::visitMemberExpr(MemberExpr &) {}
void LLVMCodeGenPrepare::visitNewExpr(NewExpr &) {}
void LLVMCodeGenPrepare::visitClassCastExpr(ClassCastExpr &) {}
void LLVMCodeGenPrepare::visitNullExpr(NullExpr &) {}
void LLVMCodeGenPrepare::visitMemberCallExpr(MemberCallExpr &) {}
void LLVMCodeGenPrepare::visitVTableExpr(VTableExpr &) {}
void LLVMCodeGenPrepare::visitMethodExpr(MethodExpr &) {}
