#include "LLVMClassCodeGen.h"
#include "ASTUtils.h"
#include <llvm/IR/IRBuilder.h>

FunctionDef *createConstructor(ClassDef &def) {
  auto *funType = new FunctionType;
  funType->returnType = def.type;
  funType->argumentTypes.push_back(def.type);

  auto *funDef = new FunctionDef(funType, getClassConstructorName(def.className));
  auto *arg = new VarDecl("arg", def.type, nullptr);
  funDef->arguments.push_back(arg);
  for (auto* fieldDecl : def.fieldDecls) {
    if (isa<VptrType>(fieldDecl->type)) {

      funDef->block.stmts.push_back(new AssignStmt(new MemberExpr(new VarExpr(arg), fieldDecl),
                                                  new VTableExpr(&def)));
      continue;
    }

    funDef->block.stmts.push_back(new AssignStmt(new MemberExpr(new VarExpr(arg), fieldDecl),
                                                 getDefaultInitializer(*fieldDecl->type)
    ));
  }

  funDef->block.stmts.push_back(new ReturnStmt(getAsRValue(new VarExpr(arg))));
  return funDef;
}


llvm::Function *emitNewOperator(llvm::Module &module, ClassDef &def) {
  auto *funType = llvm::FunctionType::get(def.type->toLLVMType(module), false);


  auto ctorName = getNewOperatorName(def.className);
  auto *function = llvm::Function::Create(funType,
                                          llvm::Function::PrivateLinkage,
                                          ctorName, &module);

  llvm::IRBuilder<> builder(module.getContext());
  llvm::BasicBlock *bb = llvm::BasicBlock::Create(module.getContext(), "entry", function);
  builder.SetInsertPoint(bb);


  auto *malloc = module.getFunction("malloc");
  auto *classType = module.getTypeByName(def.className);

  llvm::DataLayout dataLayout(&module);
  auto allocSize = dataLayout.getTypeAllocSize(classType);
  auto *allocated = builder.CreateCall(
      malloc, {llvm::ConstantInt::get(
          llvm::IntegerType::getInt64Ty(module.getContext()), allocSize)});

  auto *structVal = builder.CreateBitCast(allocated, funType->getReturnType());
  builder.CreateCall(module.getFunction(getClassConstructorName(def.className)),
                     {structVal});

  // TODO set vptr, refCount, values etc.
  builder.CreateRet(structVal);
  return function;
}
