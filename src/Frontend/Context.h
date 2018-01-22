#pragma once
#include "Diagnostic.h"


class Context {
public:
  Context(std::string fileName) : diagnostic(std::move(fileName)) {}


  Diagnostic diagnostic;
};


