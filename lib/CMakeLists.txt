set(PUBLIC_HEADERS
    include/CppBuildInfo/TranslationUnit.h
    include/CppBuildInfo/CompileUnit.h
    include/CppBuildInfo/CompilerParserFactory.h
    include/CppBuildInfo/DataParser.h
    include/CppBuildInfo/ICompilerParser.h
    include/CppBuildInfo/utils.h
)

set(PRIVATE_SOURCES
    src/TranslationUnit.cpp
    src/CompilerParserFactory.cpp
    src/DataParser.cpp
    src/GccCompilerInterface.cpp
    src/GccCompilerParser.h
    src/utils.cpp
)

source_group("Headers" FILES ${PUBLIC_HEADERS})

add_library(CppBuildInfo ${PUBLIC_HEADERS} ${PRIVATE_SOURCES})

#set_target_properties(CppBuildInfo PROPERTIES CXX_VISIBILITY_PRESET hidden)
#generate_export_header(CppBuildInfo EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/gbi_export.h")

target_link_libraries(CppBuildInfo
    PUBLIC
        Qt5::Core
)

target_include_directories(CppBuildInfo PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if (COMPILE_TESTS)
    add_subdirectory(tests)
endif()
