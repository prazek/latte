include(ExternalProject)
set(LLVM_PREFIX
        "${CMAKE_CURRENT_BINARY_DIR}/llvm/")
set(LLVM_BUILD_DIR
        "${LLVM_PREFIX}/llvm_external-build/")


set(LLVM_ROOT "${LLVM_PREFIX}/llvm/")
set(ANTLR_INCLUDE_DIR "${LLVM_BUILD_DIR}/include/")

set(LLVM_LIB
        "${LLVM_BUILD_DIR}/lib/llvm{CMAKE_STATIC_LIBRARY_SUFFIX}")

file(MAKE_DIRECTORY "${ANTLR_INCLUDE_DIR}")


ExternalProject_Add(llvm_external
        GIT_REPOSITORY https://github.com/llvm-mirror/llvm
        GIT_TAG "5.0"
        LOG_DOWNLOAD       ON
        PREFIX "${LLVM_PREFIX}"
        CONFIGURE_COMMAND "${CMAKE_COMMAND}" "${LLVM_ROOT}" "-DCMAKE_INSTALL_PREFIX=${LLVM_BUILD_DIR}"
        CMAKE_CACHE_ARGS -DCMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS}" -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
        LOG_CONFIGURE OFF
        LOG_BUILD OFF)

add_library(llvmlib IMPORTED STATIC GLOBAL)
set_target_properties(llvmlib PROPERTIES
        IMPORTED_LOCATION "${LLVM_LIB}"
        INTERFACE_INCLUDE_DIRECTORIES "${ANTLR_INCLUDE_DIR}"
        IMPORTED_LINK_INTERFACE_LIBRARIES "${LLVM_LIB}")

add_dependencies(llvmlib llvm_external)


