#include "ConstantProp.h"

#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/ConstantFolding.h"
#include "llvm/Transforms/Utils/Local.h"

#include <unordered_set>
using namespace llvm;

bool ConstantProp::runOnFunction(Function &function) {

  const DataLayout &DL = function.getParent()->getDataLayout();
  std::unordered_set<Instruction*> WorkList;
  for (Instruction &instr: instructions(&function))
    WorkList.insert(&instr);

  bool changed = false;
  while (!WorkList.empty()) {
    Instruction *instr = *WorkList.begin();
    WorkList.erase(WorkList.begin());

    if (!instr->use_empty())
      if (Constant *C = ConstantFoldInstruction(instr, DL)) {

        for (User *U : instr->users())
          WorkList.insert(cast<Instruction>(U));

        instr->replaceAllUsesWith(C);

        WorkList.erase(instr);
        if (isInstructionTriviallyDead(instr))
          instr->eraseFromParent();
        
        changed = true;
      }
  }
  return changed;
}
