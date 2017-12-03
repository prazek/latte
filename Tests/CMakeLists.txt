message("includes: ${COMMON_INCLUDES}")
include_directories(${COMMON_INCLUDES})

add_subdirectory(gtest)
enable_testing()

set(TEST_FILES FrontendTests.cpp)
set(SOURCE_FILES {$SOURCE_FILES} ${TEST_FILES})

add_executable(runTests ${TEST_FILES})

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests instant_lib)
target_link_libraries(runTests antlr4lib)

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