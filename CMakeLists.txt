project(CppBuildInfo)
cmake_minimum_required(VERSION 3.6)

include(cmake/versions.cmake              REQUIRED)
include(cmake/options.cmake               REQUIRED)
include(cmake/findDependencies.cmake      REQUIRED)
include(cmake/compilerDefinitions.cmake   REQUIRED)
include(cmake/compileroptions.cmake       REQUIRED)
include(cmake/buildFiles.cmake            REQUIRED)

add_subdirectory(lib)
add_subdirectory(apps)

include(cmake/printInfo.cmake             REQUIRED)
