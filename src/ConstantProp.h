#pragma once

#include "BasicModulePass.h"

class ConstantProp : public BasicModulePass {
public:
  bool runOnFunction(llvm::Function &F) override;
};




