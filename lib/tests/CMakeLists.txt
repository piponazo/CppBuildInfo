file(GLOB_RECURSE sources unit/*.cpp)

add_executable(tests main.cpp ${sources})
add_dependencies(tests googletest)

target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(tests
	${GTEST_LIBS_DIR}/libgtest.a
	${GTEST_LIBS_DIR}/libgtest_main.a
	CppBuildInfo
)
