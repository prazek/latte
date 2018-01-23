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
  std::unordered_set<Instruction*> workList;
  for (Instruction &instr: instructions(&function))
    workList.insert(&instr);

  bool changed = false;
  while (!workList.empty()) {
    Instruction *instr = *workList.begin();
    workList.erase(workList.begin());

    if (!instr->use_empty())
      if (Constant *constant = ConstantFoldInstruction(instr, DL)) {

        for (User *user : instr->users())
          workList.insert(cast<Instruction>(user));

        instr->replaceAllUsesWith(constant);
        workList.erase(instr);
        if (isInstructionTriviallyDead(instr))
          instr->eraseFromParent();
        
        changed = true;
      }
  }
  return changed;
}
