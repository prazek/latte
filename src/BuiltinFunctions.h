

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
         getReadFunction("readString", SimpleType::String()),
         getReadFunction("readInt", SimpleType::Int()),
         getErrorFunction(),
         getStrCatFunction()
         };
    return builtinFunctions;
  }

  static const inline std::string StringConcat = "___stringConcat";

private:
  static FunctionDef *getPrintFunction(std::string name, Type *argType) {
    auto *funType = new FunctionType;
    funType->returnType = SimpleType::Void();
    funType->argumentTypes.push_back(argType);
    return new FunctionDef(funType, std::move(name));
  };

  static FunctionDef *getReadFunction(std::string name, Type *retType) {
    auto *funType = new FunctionType;
    funType->returnType = retType;
    return new FunctionDef(funType, std::move(name));
  }

  static FunctionDef *getErrorFunction() {
    auto *funType = new FunctionType;
    funType->returnType = SimpleType::Void();
    return new FunctionDef(funType, "error");
  }

  static FunctionDef *getStrCatFunction() {
    auto *funType = new FunctionType;
    funType->returnType = SimpleType::String();
    funType->argumentTypes.push_back(SimpleType::String());
    funType->argumentTypes.push_back(SimpleType::String());
    return new FunctionDef(funType, StringConcat);
  }
};




