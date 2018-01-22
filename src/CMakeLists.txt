set(INSTC_LLVM_SOURCE_FILES "")


set(antlr_files Frontend/LatteBaseVisitor.cpp Frontend/LatteBaseVisitor.h Frontend/LatteParser.cpp Frontend/LatteParser.h
        Frontend/LatteLexer.cpp Frontend/LatteLexer.h Frontend/LatteVisitor.h Frontend/LatteVisitor.cpp Frontend/TypeChecker.cpp
        Frontend/TypeChecker.h Frontend/Type.h Frontend/Utilities.h Frontend/Diagnostic.cpp Frontend/Diagnostic.h Frontend/Context.cpp Frontend/Context.h
        LLVMCodeGen.cpp LLVMCodeGen.h Frontend/VariableScope.h Frontend/AST.cpp Frontend/AST.h Frontend/ASTVisitor.h LLVMCodeGenPrepare.cpp
        LLVMCodeGenPrepare.h BuiltinFunctions.h Frontend/ControlFlowAnalyzer.cpp Frontend/ControlFlowAnalyzer.h LLVMClassCodeGen.cpp LLVMClassCodeGen.h Frontend/ASTUtils.cpp Frontend/ASTUtils.h Mem2Reg.cpp Mem2Reg.h)

set(SOURCE_FILES ${SOURCE_FILES} ${INSTC_LLVM_SOURCE_FILES} ${antlr_files} main.cpp
        )

add_library(latte_lib ${antlr_files})
target_link_libraries(latte_lib antlr4lib)
add_dependencies(latte_lib antlr4lib)


find_package(LLVM 3.9 REQUIRED
        all-targets analysis asmparser asmprinter bitreader bitwriter codegen core debuginfocodeview debuginfodwarf debuginfomsf debuginfopdb globalisel instcombine ipa ipo instrumentation irreader libdriver linker lto mc mcdisassembler mcparser objcarcopts object option profiledata scalaropts selectiondag support tablegen target transformutils vectorize ${EXTRA_LLVM_MODULES}
        HINTS /home/students/inf/PUBLIC/MRJP/llvm39)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs support core irreader bitwriter linker)


add_executable(latc_llvm main.cpp)
target_link_libraries(latc_llvm latte_lib)
target_link_libraries(latc_llvm antlr4lib)

target_link_libraries(latc_llvm ${llvm_libs})



