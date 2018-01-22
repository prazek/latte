#pragma once
#include "llvm/Pass.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"




class Mem2Reg : llvm::ModulePass {
  static char ID;
public:
  Mem2Reg() : llvm::ModulePass(ID) {}
  bool runOnModule(llvm::Module &M) override;

private:
  bool runOnFunction(llvm::Function &F);
  bool processBlock(llvm::BasicBlock &bb, llvm::BasicBlock *predecessor);


  struct AllocaInfo {
    llvm::Value *currentValue = nullptr;
    llvm::PHINode *phi = nullptr;
  };
  std::unordered_map<llvm::BasicBlock*,
                      std::unordered_map<llvm::Value*, AllocaInfo>> info;
  llvm::SmallPtrSet<llvm::BasicBlock*, 8> visitedBlocks;
};




