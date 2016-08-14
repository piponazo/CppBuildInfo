file(GLOB_RECURSE sources src/*.cpp src/*.cc)
file(GLOB_RECURSE headers src/*.h src/*.hpp include/*.h)

add_library(CppBuildInfo ${sources} ${headers})

#set_target_properties(CppBuildInfo PROPERTIES CXX_VISIBILITY_PRESET hidden)
#generate_export_header(CppBuildInfo EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/gbi_export.h")

target_link_libraries(CppBuildInfo PUBLIC Qt5::Core)

target_include_directories(CppBuildInfo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (COMPILE_TESTS)
	add_subdirectory(tests)
endif()
