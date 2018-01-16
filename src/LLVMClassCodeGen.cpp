#include "LLVMClassCodeGen.h"
#include <llvm/IR/IRBuilder.h>

llvm::Function *emitClassConstructor(llvm::Module &module, ClassDef &def) {
  auto *funType = llvm::FunctionType::get(def.type->toLLVMType(module), false);


  auto ctorName = getClassConstructorName(def.className);
  auto *function = llvm::Function::Create(funType,
                                          llvm::Function::ExternalLinkage,
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

  // TODO set vptr, refCount, values etc.
  builder.CreateRet(
      builder.CreateBitCast(allocated, funType->getReturnType()));
  return function;
}
