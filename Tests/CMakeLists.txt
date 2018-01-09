message("includes: ${COMMON_INCLUDES}")
include_directories(${COMMON_INCLUDES})

add_subdirectory(gtest)
enable_testing()

set(TEST_FILES FrontendTests.cpp)
set(SOURCE_FILES {$SOURCE_FILES} ${TEST_FILES})

add_executable(runTests ${TEST_FILES})

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests latte_lib)
target_link_libraries(runTests antlr4lib)

find_package(LLVM 3.9 REQUIRED
        all-targets analysis asmparser asmprinter bitreader bitwriter codegen core debuginfocodeview debuginfodwarf debuginfomsf debuginfopdb globalisel instcombine ipa ipo instrumentation irreader libdriver linker lto mc mcdisassembler mcparser objcarcopts object option profiledata scalaropts selectiondag support tablegen target transformutils vectorize ${EXTRA_LLVM_MODULES}
        HINTS /home/students/inf/PUBLIC/MRJP/llvm39
        )

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs support core irreader)



message("Trying ${llvm_libs}")
target_link_libraries(runTests ${llvm_libs})

configure_lit_site_cfg(
        ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.py.in
        ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg.py
        MAIN_CONFIG
        ${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py
)

add_lit_testsuite(check "Running the Latte regression tests"
        ${CMAKE_CURRENT_BINARY_DIR}
        #LIT ${LLVM_LIT}
        PARAMS ""
        DEPENDS ""
        ARGS ""
        )
set_target_properties(check PROPERTIES FOLDER "Latte tests")

add_lit_testsuites(frontend ${CMAKE_CURRENT_SOURCE_DIR}
        PARAMS ""
        DEPENDS ""
        )