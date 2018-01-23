#pragma once

#include "llvm/Pass.h"
#include "llvm/Pass.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"

class BasicModulePass : llvm::ModulePass{
public:
  static char ID;
  BasicModulePass() : ModulePass(ID) {}

  bool runOnModule(llvm::Module &M) override;

  virtual bool runOnFunction(llvm::Function &F) = 0;

  virtual bool skipFunction(llvm::Function &F);
};




