#pragma once

#include "AST.h"
#include "llvm/IR/Function.h"
#include <string>


inline std::string getClassConstructorName(const std::string &className) {
  return className + "$ctor";
}

llvm::Function *emitClassConstructor(llvm::Module &module,
                                     ClassDef &def);

