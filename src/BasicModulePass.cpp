#include "BasicModulePass.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/InstIterator.h"

char BasicModulePass::ID;

bool BasicModulePass::runOnModule(llvm::Module &M) {
  bool changed = false;
  for (auto &fun : M.functions()) {
    if (skipFunction(fun))
      continue;
    changed |= runOnFunction(fun);
  }
  return changed;
}

bool BasicModulePass::skipFunction(llvm::Function &F) {
  return F.isDeclaration();
}

