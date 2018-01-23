#pragma once
#include "BasicModulePass.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Instructions.h"


/// This class removes allocas with loads and stores to them
/// and transform IR to SSA.
class Mem2Reg : public BasicModulePass {
private:
  bool runOnFunction(llvm::Function &F) override;
  bool processBlock(llvm::BasicBlock &bb, llvm::BasicBlock *predecessor);


  struct AllocaInfo {
    llvm::Value *currentValue = nullptr;
    llvm::PHINode *phi = nullptr;
  };
  std::unordered_map<llvm::BasicBlock*,
                      std::unordered_map<llvm::Value*, AllocaInfo>> info;
  llvm::SmallPtrSet<llvm::BasicBlock*, 8> visitedBlocks;
};




