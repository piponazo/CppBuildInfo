file(GLOB_RECURSE sources unit/*.cpp)

add_executable(tests main.cpp ${sources})
target_link_libraries(tests CppBuildInfo GTest::GTest)

#target_include_directories(tests SYSTEM PRIVATE ${INSTALL_DIR}/include)
#target_link_libraries(tests PRIVATE CppBuildInfo ${GTEST_LIBS})


# Configuration file
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/tests_config.h")
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}) # For detecting tests_config.h

