set(INSTC_LLVM_SOURCE_FILES "")


set(antlr_files LatteBaseVisitor.cpp LatteBaseVisitor.h LatteParser.cpp LatteParser.h
        LatteLexer.cpp LatteLexer.h LatteVisitor.h LatteVisitor.cpp TypeChecker.cpp
        TypeChecker.h Type.h Utilities.h Diagnostic.cpp Diagnostic.h Context.cpp Context.h)

set(SOURCE_FILES ${SOURCE_FILES} ${INSTC_LLVM_SOURCE_FILES} ${antlr_files} main.cpp
        )

add_library(instant_lib ${antlr_files})
target_link_libraries(instant_lib antlr4lib)
add_dependencies(instant_lib antlr4lib)


add_executable(latte main.cpp)
#add_dependencies(insc_llvm antlr4lib)
target_link_libraries(latte instant_lib)
target_link_libraries(latte antlr4lib)




