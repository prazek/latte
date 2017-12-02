find_package(Threads)
include(ExternalProject)
set(GTEST_PREFIX
        "${CMAKE_CURRENT_BINARY_DIR}/gtest")
set(BUILD_DIR
        "${GTEST_PREFIX}/src/gtest_external-build")
set(GTEST_DIR
        "${BUILD_DIR}/googlemock/gtest")
set(GMOCK_DIR
        "${BUILD_DIR}/googlemock")
set(GTEST_INCLUDE_DIR
        "${GTEST_PREFIX}/src/gtest_external/googletest/include")
set(GMOCK_INCLUDE_DIR
        "${GTEST_PREFIX}/src/gtest_external/googlemock/include")
set(GTEST_LIB
        "${GTEST_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(GTEST_MAIN_LIB
        "${GTEST_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(GMOCK_LIB
        "${GMOCK_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(GMOCK_MAIN_LIB
        "${GMOCK_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gmock_main${CMAKE_STATIC_LIBRARY_SUFFIX}")

file(MAKE_DIRECTORY "${GTEST_INCLUDE_DIR}")
file(MAKE_DIRECTORY "${GMOCK_INCLUDE_DIR}")

ExternalProject_Add(gtest_external
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG "ec44c6c1675c25b9827aacd08c02433cccde7780"
        INSTALL_COMMAND ""
        PREFIX "${GTEST_PREFIX}"
        LOG_BUILD   ON
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
        CMAKE_CACHE_ARGS -DBUILD_GTEST:STRING=ON -DBUILD_GMOCK:STRING=ON -DGTEST_USE_OWN_TR1_TUPLE:STRING=0)

add_library(gtest IMPORTED STATIC GLOBAL)
set_target_properties(gtest PROPERTIES
        IMPORTED_LOCATION "${GTEST_LIB}"
        INTERFACE_INCLUDE_DIRECTORIES "${GTEST_INCLUDE_DIR}"
        IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")

add_library(gtest_main IMPORTED STATIC GLOBAL)
set_target_properties(gtest_main PROPERTIES
        IMPORTED_LOCATION "${GTEST_MAIN_LIB}"
        IMPORTED_LINK_INTERFACE_LIBRARIES "${GTEST_LIB};${CMAKE_THREAD_LIBS_INIT}")

add_library(gmock IMPORTED STATIC GLOBAL)
set_target_properties(gmock PROPERTIES
        IMPORTED_LOCATION "${GMOCK_LIB}"
        INTERFACE_INCLUDE_DIRECTORIES "${GMOCK_INCLUDE_DIR}"
        IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")

add_library(gmock_main IMPORTED STATIC GLOBAL)
set_target_properties(gmock_main PROPERTIES
        IMPORTED_LOCATION "${GMOCK_MAIN_LIB}"
        IMPORTED_LINK_INTERFACE_LIBRARIES "${GMOCK_LIB};${CMAKE_THREAD_LIBS_INIT}")

add_dependencies(gtest gtest_external)
add_dependencies(gtest_main gtest_external)
add_dependencies(gmock gtest_external)
add_dependencies(gmock_main gtest_external)