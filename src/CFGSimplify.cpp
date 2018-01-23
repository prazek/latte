#include <iostream>
#include "CFGSimplify.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/ConstantFolding.h"
#include "llvm/Analysis/InstructionSimplify.h"
#include "llvm/Transforms/Utils/Local.h"

#include "llvm/Transforms/Utils/BasicBlockUtils.h"

using namespace llvm;

static bool runInBlock(BasicBlock &BB) {
  bool changed = false;

  auto *instr = BB.getTerminator();
  if (auto *branch = dyn_cast_or_null<BranchInst>(instr)) {
    if (branch->isUnconditional()) {
      auto *succ = branch->getSuccessor(0);
      if (succ->getSinglePredecessor()) {
        changed |= MergeBlockIntoPredecessor(succ);
      }

    } else {
      assert(branch->isConditional());

      auto removeBlockPhiUsages = [](BasicBlock *from, BasicBlock *removedEdgeTo) {
        for (auto &I : *removedEdgeTo) {
          if (auto *phi = dyn_cast<PHINode>(&I)) {
            phi->removeIncomingValue(from);
          }
        }

      };
      if (auto *constant = dyn_cast<Constant>(branch->getCondition())) {
        if (constant->isOneValue()) {
          auto *removedEdgeTo = branch->getSuccessor(1);
          auto *deadBlock = removedEdgeTo->getSinglePredecessor()
                            ? removedEdgeTo : nullptr;

          auto *newBranch = BranchInst::Create(branch->getSuccessor(0));

          removeBlockPhiUsages(&BB, removedEdgeTo);

          ReplaceInstWithInst(branch, newBranch);
          DeleteDeadPHIs(removedEdgeTo);
          if (deadBlock)
            DeleteDeadBlock(deadBlock);
        } else {

          auto *removedEdgeTo = branch->getSuccessor(0);
          auto *deadBlock = removedEdgeTo->getSinglePredecessor()
                            ? removedEdgeTo : nullptr;

          auto *newBranch = BranchInst::Create(branch->getSuccessor(1));
          removeBlockPhiUsages(&BB, removedEdgeTo);
          ReplaceInstWithInst(branch, newBranch);
          DeleteDeadPHIs(removedEdgeTo);
          if (deadBlock)
            DeleteDeadBlock(deadBlock);


        }
      }

    }
  }
  return changed;
}

bool CFGSimplify::runOnFunction(llvm::Function &function) {
  bool changed = false;

  for (auto &BB : function) {
    changed |= runInBlock(BB);
  }

  return changed;
}
bool CFGSimplify::runOnModule(llvm::Module &module) {
  do {
    //module.dump();
  } while (BasicModulePass::runOnModule(module));
  return false;
}
