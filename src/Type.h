#pragma once
#include <memory>
#include <vector>

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


  static SimpleType Int() {
    return SimpleType(POD::Int);
  }

  static SimpleType Void() {
    return SimpleType(POD::Void);
  }

  static SimpleType Bool() {
    return SimpleType(POD::Bool);
  }

  static SimpleType String() {
    return SimpleType(POD::String);
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
  }


  POD getPOD() const { return pod; }

  ~SimpleType() override = default;
private:
  POD pod;
};


class FunctionType final : public Type {
  std::unique_ptr<Type> returnType;
  std::vector<std::unique_ptr<Type>> argumentTypes;

public:
  bool operator==(const Type& other) const override {
    return other == *this;
  }
  bool operator==(const SimpleType &) const override {
    return false;
  }

  bool operator==(const FunctionType &other) const override {
    return std::tie(returnType, argumentTypes) ==
      std::tie(other.returnType, other.argumentTypes);
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
};

