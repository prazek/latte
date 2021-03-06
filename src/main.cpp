#include "antlr4-runtime.h"
#include "Frontend/ControlFlowAnalyzer.h"
#include "Frontend/LatteLexer.h"
#include "Frontend/LatteParser.h"
#include "Frontend/TypeChecker.h"
#include "LLVMCodeGen/LLVMCodeGen.h"
#include "LLVMCodeGen/LLVMCodeGenPrepare.h"
#include "Mem2Reg.h"

#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/raw_os_ostream.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/Linker/Linker.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "ConstantProp.h"
#include "CFGSimplify.h"

#include <string>
#include <fstream>


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


class ErrorListener : public ConsoleErrorListener {
public:
  ErrorListener(std::string fileName) : fileName(std::move(fileName)) {}

  void syntaxError(Recognizer *,
                   Token *,
                   size_t line,
                   size_t charPositionInLine,
                   const std::string &msg,
                   std::exception_ptr) override {
    if (!hadError) {
      std::cerr << "ERROR\n";
      hadError = true;
    }

    std::cerr << fileName << ":"
              << line << ":"
              << charPositionInLine << ": error: " << msg << std::endl;
  }

  bool hadError = false;
  std::string fileName;
};

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    printf("latte language compiler\n");
    printf("Usage: %s file.lat\n", argv[0]);
    exit(1);
  }

  std::string fileName = argv[1];
  auto file = openFile(argv[1]);
  auto parsedFile = parseFileName(argv[1]);
  auto llvmFileName = parsedFile + ".ll";
  auto bcFileName = parsedFile + ".bc";

  ANTLRInputStream input(file);
  LatteLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  tokens.fill();

  ErrorListener errorListener(fileName);
  LatteParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(&errorListener);

  auto *program = parser.program();
  if (errorListener.hadError)
    return 2;

  Context context(fileName);

  TypeChecker typeChecker(context);
  typeChecker.visit(program);

  if (context.diagnostic.hadError)
    return 3;

  ControlFlowAnalyzer controlFlowAnalyzer(context.diagnostic);
  controlFlowAnalyzer.visitAST(typeChecker.ast);

  if (context.diagnostic.hadError)
    return 4;

  llvm::LLVMContext llvmContext;
  std::unique_ptr<llvm::Module> module = std::make_unique<llvm::Module>(parsedFile, llvmContext);

  LLVMCodeGenPrepare codeGenPrepare(*module);
  codeGenPrepare.visitAST(typeChecker.ast);
  //std::cerr << typeChecker.ast.dump();

  LLVMCodeGen codeGen(*module);
  codeGen.visitAST(typeChecker.ast);
  //llvm::verifyModule(*module, &llvm::errs());

  Mem2Reg mem2Reg;
  mem2Reg.runOnModule(*module);

  ConstantProp constantProp;
  constantProp.runOnModule(*module);

  CFGSimplify cfgSimplify;
  cfgSimplify.runOnModule(*module);

  //module->print(llvm::errs(), nullptr);
  std::fstream outFile(llvmFileName, std::ios_base::out);

  llvm::raw_os_ostream ostream(outFile);
  module->print(ostream, nullptr);
  ostream.flush();
  outFile.flush();


  std::fstream outBcFile(bcFileName, std::ios_base::out);
  llvm::raw_os_ostream bitcodeOstream(outBcFile);


  auto Composite = std::make_unique<llvm::Module>("llvm-link", llvmContext);
  llvm::Linker L(*Composite);
  L.linkInModule(std::move(module));

  llvm::SMDiagnostic Err;
  std::unique_ptr<llvm::Module> Result =
      llvm::getLazyIRFileModule("lib/runtime.ll", Err, llvmContext);

  if (!Result) {
    printf("Error! cant load runtime.ll");
    return 42;
  }

  if (L.linkInModule(std::move(Result))) {
    std::cerr << "Error in linking";
    return 43;
  }

  ostream.flush();

  WriteBitcodeToFile(Composite.get(), bitcodeOstream);
  bitcodeOstream.flush();

  std::cerr << "OK\n";
  return 0;
}