#pragma once

#include "Utilities.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"
#include <memory>
#include <vector>
#include <sstream>
#include <unordered_map>

class SimpleType;
class FunctionType;

class Type {
public:
  bool operator !=(const Type &other) const {
    return !(*this == other);
  }
  virtual bool operator==(const Type&) const = 0;
  virtual bool operator==(const SimpleType&) const = 0;
  virtual bool operator==(const FunctionType&) const = 0;

  virtual llvm::Type* toLLVMType(llvm::LLVMContext &c) const = 0;

  virtual std::string toString() const = 0;
  virtual ~Type() = 0;
};
inline Type::~Type() {}

class SimpleType final : public Type {
public:
  enum class POD {
    Void,
    Int,
    Bool,
    String,
  };

  SimpleType(POD pod) : pod(pod) {}
  SimpleType(const SimpleType&) = default;
  SimpleType(SimpleType&&) = default;


  static SimpleType* Int() {
    return new SimpleType(POD::Int);
  }

  static SimpleType* Void() {
    return new SimpleType(POD::Void);
  }

  static SimpleType* Bool() {
    return new SimpleType(POD::Bool);
  }

  static SimpleType* String() {
    return new SimpleType(POD::String);
  }

  bool operator==(const Type& other) const override {
    return other == *this;
  }
  bool operator==(const SimpleType &other) const override {
    return pod == other.pod;
  }
  virtual bool operator==(const FunctionType&) const override {
    return false;
  }

  bool isVoid() const {
    return pod == POD::Void;
  }

  bool isInt() const {
    return pod == POD::Int;
  }
  bool isBool() const {
    return pod == POD::Bool;
  }

  bool isString() const {
    return pod == POD::String;
  }

  std::string toString() const override {
    switch (pod) {
      case POD::Void:
        return "void";
      case POD::Bool:
        return "boolean";
      case POD::Int:
        return "int";
      case POD::String:
        return "string";
    }
    assert(false && "Unreachable");
  }

  llvm::Type *toLLVMType(llvm::LLVMContext &c) const override {
    switch (pod) {
      case POD::Void:
        return llvm::Type::getVoidTy(c);
      case POD::Bool:
        return llvm::Type::getInt1Ty(c);
      case POD::Int:
        return llvm::Type::getInt32Ty(c);
      case POD::String:
        return llvm::Type::getInt8PtrTy(c);
    }
    assert(false);
  }

  POD getPOD() const { return pod; }

  ~SimpleType() override = default;
private:
  POD pod;
};


class FunctionType final : public Type {
public:
  Type *returnType;
  std::vector<Type*> argumentTypes;

  bool operator==(const Type& other) const override {
    return other == *this;
  }
  bool operator==(const SimpleType &) const override {
    return false;
  }

  bool operator==(const FunctionType &other) const override {
    if (*returnType != *other.returnType)
      return false;
    if (argumentTypes.size() != other.argumentTypes.size())
      return false;
    for (unsigned i = 0; i < argumentTypes.size(); i++)
      if (*argumentTypes[i] != *other.argumentTypes[i])
        return false;
    return true;
  }

  std::string toString() const override {
    std::stringstream ss;
    ss << returnType->toString() << " (";

    bool first = true;
    for (auto &&argType : argumentTypes) {
      if (!first)
        ss << ", ";
      ss << argType->toString();
      first = false;
    }
    ss << ")";
    return ss.str();
  }

  llvm::Type *toLLVMType(llvm::LLVMContext &c) const override {
    llvm::Type * retTy = returnType->toLLVMType(c);
    llvm::SmallVector<llvm::Type*, 4> argTypes;
    for (Type *argType : argumentTypes) {
      argTypes.push_back(argType->toLLVMType(c));
    }

    return llvm::FunctionType::get(retTy, argTypes, false);
  }
};


class ClassType final : public Type {
public:
  std::unordered_map<std::string, Type*> types;
  std::string name;
  ClassType *baseClass = nullptr;

  std::string toString() const override {
    return name;
  }

  std::string dump() const {
    std::stringstream ss;
    ss << "class " << name;
    if (baseClass)
      ss << " : " << baseClass->name;
    ss << " {\n";

    for (const auto &p : types) {
      ss << p.first << " " << p.second->toString() << ";\n";
    }
    ss << ")";
    return ss.str();
  }

  bool operator==(const Type& type) const override {
    if (const auto *ct = dyn_cast<ClassType>(&type)) {
      // Let's add ODR to the language so that this code is correct.
      return name == ct->name;
    }
    return false;
  }
  bool operator==(const SimpleType&) const override {
    return false;
  }
  bool operator==(const FunctionType&) const override {
    return false;
  }

  llvm::Type* toLLVMType(llvm::LLVMContext &) const override {
    assert(false);
    return nullptr;
  }

};
