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

add_test(NAME that-test-I-made COMMAND runUnitTests)
add_test(that-other-test-I-made runUnitTests)