
set(frontend_files LatteBaseVisitor.cpp LatteBaseVisitor.h LatteParser.cpp LatteParser.h
        LatteLexer.cpp LatteLexer.h LatteVisitor.h LatteVisitor.cpp TypeChecker.cpp
        TypeChecker.h Type.h Utilities.h Diagnostic.cpp Diagnostic.h Context.cpp Context.h
        VariableScope.h AST.cpp AST.h ASTVisitor.h
        ControlFlowAnalyzer.cpp ControlFlowAnalyzer.h ASTUtils.cpp ASTUtils.h )

set(SOURCE_FILES ${SOURCE_FILES} ${INSTC_LLVM_SOURCE_FILES} ${frontend_files} main.cpp
        )

add_library(frontend_lib ${frontend_files})
add_dependencies(frontend_lib antlr4lib)
target_link_libraries(frontend_lib antlr4lib)


# FIXME Frontend should not depend on LLVM.
find_package(LLVM 3.9 REQUIRED
        support core irreader bitwriter linker
        HINTS /home/students/inf/PUBLIC/MRJP/llvm39)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs support core irreader bitwriter linker)
target_link_libraries(frontend_lib ${llvm_libs})

