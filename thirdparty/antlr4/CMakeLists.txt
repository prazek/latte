
include(ExternalProject)
set(ANTLR_PREFIX
        "${CMAKE_CURRENT_BINARY_DIR}/antlr4")
set(BUILD_DIR
        "${ANTLR_PREFIX}/src/antlr4_external-build/")


set(ANTLR4_ROOT "${ANTLR_PREFIX}/src/antlr4_external/runtime/Cpp/")
set(ANTLR_INCLUDE_DIR "${BUILD_DIR}/include/antlr4-runtime/")

set(ANTLR4_LIB
        "${BUILD_DIR}/lib/libantlr4-runtime${CMAKE_STATIC_LIBRARY_SUFFIX}")

file(MAKE_DIRECTORY "${ANTLR_INCLUDE_DIR}")


ExternalProject_Add(antlr4_external
        GIT_REPOSITORY https://github.com/antlr/antlr4.git
        GIT_TAG "d4d7e3d3bc3b65bb00579fe826834a9263fa45e6"
        LOG_DOWNLOAD       ON
        PREFIX "${ANTLR_PREFIX}"
        CONFIGURE_COMMAND "${CMAKE_COMMAND}" "${ANTLR4_ROOT}" "-DCMAKE_INSTALL_PREFIX=${BUILD_DIR}"
        CMAKE_CACHE_ARGS -DCMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS}" -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
        LOG_CONFIGURE OFF
        LOG_BUILD OFF
        LOG_INSTALL OFF)

add_library(antlr4lib IMPORTED STATIC GLOBAL)
set_target_properties(antlr4lib PROPERTIES
        IMPORTED_LOCATION "${ANTLR4_LIB}"
        INTERFACE_INCLUDE_DIRECTORIES "${ANTLR_INCLUDE_DIR}"
        IMPORTED_LINK_INTERFACE_LIBRARIES "${ANTLR4_LIB}")

add_dependencies(antlr4lib antlr4_external)
