#pragma once

#include "Utilities.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"
#include <memory>
#include <vector>
#include <sstream>
#include <unordered_map>

class SimpleType;
class FunctionType;
class DerefType;

class Type {
public:
  bool operator !=(const Type &other) const {
    return !(*this == other);
  }
  virtual bool operator==(const Type& other) const = 0;

  virtual llvm::Type* toLLVMType(llvm::Module &c) const = 0;

  virtual std::string toString() const = 0;
  virtual int bytesSize() const = 0;
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

  bool operator==(const Type &other) const override {
    if (auto *simpleOther = dyn_cast<SimpleType>(other))
      return pod == simpleOther->pod;
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
    llvm_unreachable("unhandled type");
  }

  int bytesSize() const override {
    switch (pod) {
    case POD::Void:
      return 0;
    case POD::Bool:
      return 1;
    case POD::Int:
      return 4;
    case POD::String:
      return 8;
    }
    llvm_unreachable("unhandled type");
  }

  static bool isIntegral(const Type& type) {
    if (auto *st = dyn_cast<SimpleType>(type))
      return st->isInt();
    return false;
  }

  static bool isString(const Type& type) {
    if (auto *st = dyn_cast<SimpleType>(type))
      return st->isString();
    return false;
  }

  static bool isBoolean(const Type& type) {
    if (auto *st = dyn_cast<SimpleType>(type))
      return st->isBool();
    return false;
  }

  static bool isVoid(const Type& type) {
    if (auto *st = dyn_cast<SimpleType>(type))
      return st->isVoid();
    return false;
  }

  llvm::Type *toLLVMType(llvm::Module &module) const override {
    switch (pod) {
      case POD::Void:
        return llvm::Type::getVoidTy(module.getContext());
      case POD::Bool:
        return llvm::Type::getInt1Ty(module.getContext());
      case POD::Int:
        return llvm::Type::getInt32Ty(module.getContext());
      case POD::String:
        return llvm::Type::getInt8PtrTy(module.getContext());
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


  bool operator==(const Type &other) const override {
    if (auto *otherFun = dyn_cast<FunctionType>(other))
      return this->operator==(*otherFun);
    return false;
  }

  bool operator==(const FunctionType &other) const {
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

  int bytesSize() const override {
    return 8;
  }

  llvm::Type *toLLVMType(llvm::Module &module) const override {
    llvm::Type * retTy = returnType->toLLVMType(module);
    llvm::SmallVector<llvm::Type*, 4> argTypes;
    for (Type *argType : argumentTypes) {
      argTypes.push_back(argType->toLLVMType(module));
    }

    return llvm::FunctionType::get(retTy, argTypes, false);
  }
};

struct ClassDef;

class ClassType final : public Type {
public:
  ClassType(std::string name)
      : name(std::move(name)) {}

  std::string name;

  std::string toString() const override {
    return name;
  }

  std::string dump() const {
    return "Class:";
  }

  int bytesSize() const override {
    return 8;
  }

  bool operator==(const Type& type) const  {
    if (const auto *ct = dyn_cast<ClassType>(&type)) {
      // Let's add ODR to the language so that this code is correct.
      return name == ct->name;
    }
    return false;
  }

  llvm::Type* toLLVMType(llvm::Module &module) const override {
    return llvm::PointerType::get(module.getTypeByName(name), 0);
  }
};
