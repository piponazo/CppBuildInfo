cmake_minimum_required(VERSION 3.10)

project(CppBuildInfo
    LANGUAGES CXX
    VERSION 0.0.1
)

include(cmake/basicSetup.cmake            REQUIRED)
include(cmake/options.cmake               REQUIRED)
include(cmake/findDependencies.cmake      REQUIRED)
include(cmake/compilerDefinitions.cmake   REQUIRED)
include(cmake/compileroptions.cmake       REQUIRED)
include(cmake/buildFiles.cmake            REQUIRED)

add_subdirectory(lib)
add_subdirectory(apps)

include(cmake/printInfo.cmake             REQUIRED)
