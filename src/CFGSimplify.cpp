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

      if (auto *constant = dyn_cast<Constant>(branch->getCondition())) {
        if (constant->isOneValue()) {
          auto *deadBlock = branch->getSuccessor(1)->getSinglePredecessor()
                            ? branch->getSuccessor(1) : nullptr;

          auto *newBranch = BranchInst::Create(branch->getSuccessor(0));
          ReplaceInstWithInst(branch, newBranch);
          if (deadBlock) {
            DeleteDeadBlock(deadBlock);
            //deadBlock->removePredecessor(&BB);
          }

        } else {
          auto *deadBlock = branch->getSuccessor(0)->getSinglePredecessor()
                            ? branch->getSuccessor(0) : nullptr;

          auto *newBranch = BranchInst::Create(branch->getSuccessor(1));
          ReplaceInstWithInst(branch, newBranch);

          if (deadBlock) {
            DeleteDeadBlock(deadBlock);
            //deadBlock->removePredecessor(&BB);
          }


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
  while (BasicModulePass::runOnModule(module)) {}
  return false;
}
