#pragma once

#include "BasicModulePass.h"
class CFGSimplify : public BasicModulePass {
  bool runOnFunction(llvm::Function &F) override;
public:
  bool runOnModule(llvm::Module &module) override;

};




