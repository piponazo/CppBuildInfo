file(GLOB_RECURSE sources unit/*.cpp)
set(DATA_FILES
	${PROJECT_SOURCE_DIR}/data/fakeFile4ConcurrentCompilations.txt
	${PROJECT_SOURCE_DIR}/data/fakeFile5ConcurrentCompilations.txt
	${PROJECT_SOURCE_DIR}/data/fakeFile6ConcurrentCompilations.txt
)

add_executable(tests main.cpp ${sources} ${DATA_FILES})
target_link_libraries(tests CppBuildInfo GTest::GTest)

# Configuration file
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/tests_config.h")
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}) # For detecting tests_config.h

