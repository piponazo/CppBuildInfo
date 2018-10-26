set(PUBLIC_HEADERS
    include/CppBuildInfo/ICompilerParser.h
    include/CppBuildInfo/TranslationUnit.h
    include/CppBuildInfo/CompileUnit.h
    include/CppBuildInfo/CompilerParserFactory.h
    include/CppBuildInfo/DataParser.h
    include/CppBuildInfo/utils.h
)

set(PRIVATE_SOURCES
    src/TranslationUnit.cpp
    src/CompilerParserFactory.cpp
    src/DataParser.cpp
    src/GccCompilerParser.cpp
    src/GccCompilerParser.h
    src/utils.cpp
)

source_group("Headers" FILES ${PUBLIC_HEADERS})

add_library(CppBuildInfo ${PUBLIC_HEADERS} ${PRIVATE_SOURCES})

generate_export_header(CppBuildInfo
    EXPORT_MACRO_NAME CBI_EXPORT
    EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/cbi_export.h"
)

target_link_libraries(CppBuildInfo
    PUBLIC
        Qt5::Core
)

target_include_directories(CppBuildInfo PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}> # For the export header
    $<INSTALL_INTERFACE:include>
)

if (COMPILE_TESTS)
    add_subdirectory(tests)
endif()
