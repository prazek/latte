#include "antlr4-runtime.h"
#include "LatteLexer.h"
#include "LatteParser.h"
#include "TypeChecker.h"
#include "LLVMCodeGen.h"
#include "LLVMCodeGenPrepare.h"
#include <string>
#include <fstream>
#include <llvm/Support/raw_ostream.h>

using namespace antlr4;

std::fstream openFile(const std::string &fileName) {
  std::fstream instantFile(fileName, std::ios_base::in);
  if (!instantFile.is_open()) {
    printf("Could not open file [%s]", fileName.c_str());
    exit(1);
  }
  return instantFile;
}

std::string parseFileName(const std::string& fullName) {
  auto dot = fullName.rfind('.');
  if (dot ==  std::string::npos)
    return fullName;
  return fullName.substr(0, dot);
}


int main(int argc, const char* argv[]) {
  if (argc != 2) {
    printf("instant language compiler\n");
    printf("Usage: %s file.lat\n", argv[0]);
    exit(1);
  }

  std::string fileName = argv[1];
  auto file = openFile(argv[1]);
  auto parsedFile = parseFileName(argv[1]);
  auto llvmFileName = parsedFile + ".ll";
  auto bcFileName = parsedFile + ".bc";
  //std::fstream outFile(llvmFileName, std::ios_base::out);


  ANTLRInputStream input(file);
  LatteLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  tokens.fill();

  LatteParser parser(&tokens);
  auto *program = parser.program();

  Context context(fileName);

  TypeChecker typeChecker(context);
  typeChecker.visit(program);

  llvm::LLVMContext llvmContext;
  std::unique_ptr<llvm::Module> module = std::make_unique<llvm::Module>("file", llvmContext);

  LLVMCodeGenPrepare codeGenPrepare(*module);
  codeGenPrepare.visitAST(typeChecker.ast);

  LLVMCodeGen codeGen(typeChecker, *module);
  codeGen.visitAST(typeChecker.ast);

  module->print(llvm::errs(), nullptr);


}