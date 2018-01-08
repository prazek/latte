#pragma once

#include <string>
#include "antlr4-runtime.h"

class Diagnostic {
public:
  Diagnostic(std::string fileName) : fileName(std::move(fileName)) {}

  void issueError(const std::string &msg, antlr4::ParserRuleContext *ctx);



  bool hadError = false;
private:
  std::string fileName;
};

