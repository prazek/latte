

#pragma once

#include "Type.h"
#include "AST.h"
#include <string>
#include <vector>

class BuiltinFunctions {
public:
  static const std::vector<FunctionDef*>& getBuiltinFunctions() {
    static const std::vector<FunctionDef*> builtinFunctions =
        {getPrintFunction("printString", SimpleType::String()),
         getPrintFunction("printInt", SimpleType::Int()),
         getPrintFunction("printBoolean", SimpleType::Bool())};
    return builtinFunctions;
  }

private:
  static FunctionDef *getPrintFunction(std::string name, Type *argType) {
    auto *funType = new FunctionType;
    funType->returnType = SimpleType::Void();
    funType->argumentTypes.push_back(argType);
    return new FunctionDef(funType, name);
  };

};




