#pragma once

#include "../Frontend/AST.h"
#include "llvm/IR/Function.h"
#include <string>


inline std::string getClassConstructorName(const std::string &className) {
  return className + "$ctor";
}

inline std::string getNewOperatorName(const std::string &className) {
  return className + "$new";
}

inline std::string mangleMethodName(const std::string &className,
                                    const std::string methodName) {
  return className + "$$" + methodName;
}

FunctionDef *createConstructor(ClassDef &def);

llvm::Function *emitNewOperator(llvm::Module &module,
                                     ClassDef &def);

