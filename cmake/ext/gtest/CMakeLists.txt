include(ExternalProject)

ExternalProject_Add(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    CMAKE_ARGS -Dgtest_force_shared_crt=ON
               -DBUILD_SHARED_LIBS=OFF
               -Dgtest_disable_pthreads=ON
               -Dgtest_build_tests=OFF
               -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/install
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
)

set(GTEST_INCLUDE_DIRS ${PROJECT_BINARY_DIR}/install/include PARENT_SCOPE)
set(GTEST_LIBS_DIR ${PROJECT_BINARY_DIR}/install/lib)
#message("GTEST_LIBS_DIR : ${GTEST_LIBS_DIR}")

if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU OR ${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    set(GTEST_LIBS ${GTEST_LIBS_DIR}/libgtest.a
                   ${GTEST_LIBS_DIR}/libgtest_main.a
                   PARENT_SCOPE)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(GTEST_LIBS ${GTEST_LIBS_DIR}/gtest.lib
                   ${GTEST_LIBS_DIR}/gtest_main.lib
                   PARENT_SCOPE)
endif()

