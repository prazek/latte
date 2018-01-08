#include "Diagnostic.h"

void Diagnostic::issueError(const std::string &msg, antlr4::ParserRuleContext *ctx) {
  if (!hadError) {
    std::cerr << "ERROR\n";
    hadError = true;
  }

  std::cerr << fileName << ":"
    << ctx->getStart()->getLine() << ":"
    << ctx->getStart()->getCharPositionInLine() << ": error: " << msg << std::endl;

}
