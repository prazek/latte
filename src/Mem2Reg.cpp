#include "Mem2Reg.h"

#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Analysis/CFG.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/InstructionSimplify.h"
using namespace llvm;

char Mem2Reg::ID;

static bool canHandleAlloca(AllocaInst *alloca) {
  for (auto *user : alloca->users())
    if (!isa<LoadInst>(user) && !isa<StoreInst>(user))
      return false;

  return true;
}



bool Mem2Reg::runOnFunction(Function &F) {
  if (F.isDeclaration())
    return false;


  for (auto &instr : F.getEntryBlock()) {
    if (auto *alloca = dyn_cast<AllocaInst>(&instr)) {
      if (canHandleAlloca(alloca)) {
        info[&F.getEntryBlock()][alloca] = {};
      }
    }
  }




  SmallVector<std::pair<BasicBlock*, BasicBlock*>, 8> blocksWorklist;
  blocksWorklist.emplace_back(&F.getEntryBlock(), nullptr);

  while (!blocksWorklist.empty()) {
    auto [bb, predecessor] = blocksWorklist.pop_back_val();
    if (!processBlock(*bb, predecessor))
      continue;
    for (BasicBlock * succ : successors(bb))
      blocksWorklist.push_back({succ, bb});
  }

  for (auto it = inst_begin(F); it != inst_end(F); ) {
    auto &instr = *it;
    it++;
    if (isa<AllocaInst>(instr) && instr.user_empty())
      instr.removeFromParent();
    if (auto *phi = dyn_cast<PHINode>(&instr)) {
      if (auto *val = phi->hasConstantValue()) {
        phi->replaceAllUsesWith(val);
        phi->removeFromParent();
      }
    }
  }

  return true;
}
bool Mem2Reg::runOnModule(Module &M) {

    for (auto &fun : M.functions()) {
      runOnFunction(fun);
    }
  return true;
}
bool Mem2Reg::processBlock(BasicBlock &bb, BasicBlock *predecessor) {
  //bb.dump();
  if (bb.getSinglePredecessor()) {
    assert(predecessor);
    for (auto & [alloca, allocaInfo] : info[predecessor]) {
      info[&bb][alloca].currentValue = allocaInfo.currentValue;
    }
  }
  else if (predecessor) {
    //predecessor->dump();
    // Create phi for every incoming value
    for (auto & [alloca, allocaInfo] : info[predecessor]) {
      if (!allocaInfo.currentValue)
        continue;
      if (!info[&bb][alloca].phi) {
        auto point = bb.getFirstInsertionPt();
        info[&bb][alloca].phi =
            PHINode::Create(cast<AllocaInst>(alloca)->getAllocatedType(),
                            0,
                            "",
                            &*point);

      }
      info[&bb][alloca].phi->addIncoming(allocaInfo.currentValue,
                                         predecessor);
      info[&bb][alloca].currentValue = info[&bb][alloca].phi;
    }
  }


  if (visitedBlocks.count(&bb))
    return false;

  visitedBlocks.insert(&bb);

  for (auto it = bb.begin(); it != bb.end(); ) {
    auto &instr = *it;
    it++;
    if (auto *store = dyn_cast<StoreInst>(&instr)) {
      auto *addr = store->getPointerOperand()->stripPointerCasts();
      if (info[&bb].count(addr) == 0)
        continue;

      info[&bb][addr].currentValue = store->getValueOperand();
      store->eraseFromParent();
      continue;
    }
    if (auto *load = dyn_cast<LoadInst>(&instr)) {
      auto *addr = load->getPointerOperand()->stripPointerCasts();
      if (info[&bb].count(addr) == 0)
        continue;

      load->replaceAllUsesWith(info[&bb][addr].currentValue);
      load->eraseFromParent();

      continue;
    }

  }
  return true;
};