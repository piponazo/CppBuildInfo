file(GLOB_RECURSE sources unit/*.cpp)

add_executable(tests main.cpp ${sources})
add_dependencies(tests gtest)

#message("GTEST_INCLUDE_DIRS : ${GTEST_INCLUDE_DIRS}")
#message("GTEST LIBSSSSS: ${GTEST_LIBS}")
#message("GTEST DIR: ${GTEST_LIBS_DIR}")

#link_directories(${GTEST_LIBS_DIR})

ExternalProject_Get_Property(gtest INSTALL_DIR)
message("GTEST INCLUDE DIR: ${INSTALL_DIR}/include")

if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU OR ${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    set(GTEST_LIBS ${INSTALL_DIR}/lib/libgtest.so
                   ${INSTALL_DIR}/lib/libgtest_main.so)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(GTEST_LIBS ${INSTALL_DIR}/lib/gtest.lib
                   ${INSTALL_DIR}/lib/gtest_main.lib)
endif()

target_include_directories(tests SYSTEM PRIVATE ${INSTALL_DIR}/include)

target_link_libraries(tests PRIVATE CppBuildInfo ${GTEST_LIBS})


# Configuration file
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/tests_config.h")
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}) # For detecting tests_config.h

