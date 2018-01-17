#pragma once

#include "AST.h"
#include "llvm/IR/Function.h"
#include <string>


inline std::string getClassConstructorName(const std::string &className) {
  return className + "$ctor";
}

inline std::string getNewOperatorName(const std::string &className) {
  return className + "$new";
}


FunctionDef *createConstructor(ClassDef &def);

llvm::Function *emitNewOperator(llvm::Module &module,
                                     ClassDef &def);

