#pragma once

#include "llvm/Pass.h"

class BasicModulePass : llvm::ModulePass{
public:
  static char ID;
  BasicModulePass() : ModulePass(ID) {}

  bool runOnModule(llvm::Module &module) override;

  virtual bool runOnFunction(llvm::Function &function) = 0;

  virtual bool skipFunction(llvm::Function &function);
};




