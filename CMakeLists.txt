cmake_minimum_required(VERSION 3.2)
project(CppBuildInfo LANGUAGES CXX VERSION 0.0.1)

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_set_find_paths()
else()
    message(WARNING "You can use conan to install the project dependencies")
endif()

include(cmake/options.cmake               REQUIRED)
include(cmake/findDependencies.cmake      REQUIRED)
include(cmake/compilerDefinitions.cmake   REQUIRED)
include(cmake/compileroptions.cmake       REQUIRED)
include(cmake/buildFiles.cmake            REQUIRED)

add_subdirectory(lib)
add_subdirectory(apps)

include(cmake/printInfo.cmake             REQUIRED)
