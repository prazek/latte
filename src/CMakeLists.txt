set(INSTC_LLVM_SOURCE_FILES "")

add_subdirectory(Frontend)

set(antlr_files LLVMCodeGen/LLVMCodeGenPrepare.cpp
        LLVMCodeGen/LLVMCodeGenPrepare.h Frontend/BuiltinFunctions.h
        LLVMCodeGen/LLVMClassCodeGen.cpp LLVMCodeGen/LLVMClassCodeGen.h LLVMCodeGen/LLVMCodeGen.h LLVMCodeGen/LLVMCodeGen.cpp
        Mem2Reg.cpp Mem2Reg.h ConstantProp.cpp ConstantProp.h BasicModulePass.cpp BasicModulePass.h CFGSimplify.cpp CFGSimplify.h)

set(SOURCE_FILES ${SOURCE_FILES} ${INSTC_LLVM_SOURCE_FILES} ${antlr_files} main.cpp
        )

add_library(latte_lib ${antlr_files})
target_link_libraries(latte_lib frontend_lib)



find_package(LLVM 3.9 REQUIRED
        support core irreader bitwriter linker ${EXTRA_LLVM_MODULES}
        HINTS /home/students/inf/PUBLIC/MRJP/llvm39)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs support core irreader bitwriter linker)


add_executable(latc_llvm main.cpp)
target_link_libraries(latc_llvm latte_lib)
target_link_libraries(latc_llvm antlr4lib)

target_link_libraries(latc_llvm ${llvm_libs})



