cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

project(instant)


if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
            "Choose the type of build, options are: Debug Release
            RelWithDebInfo MinSizeRel."
            FORCE)

    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

#set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")# -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC")

#set(ENABLE_SANITIZERS ON)
if (ENABLE_SANITIZERS)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif()

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/src)

set(LLVM_EXTERNAL_LIT "${PROJECT_SOURCE_DIR}/thirdparty/llvm/lit/lit.py")
add_subdirectory(thirdparty)

include(thirdparty/llvm/AddLLVM.cmake)

add_subdirectory(src)
add_subdirectory(Tests)






