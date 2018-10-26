add_executable(tests_unit
    main.cpp
    gtestWrapper.h
    unit/test_DataParser.cpp
    unit/test_CompilationProcess.cpp
    unit/test_utils.cpp
)

add_executable(tests_integration
    main.cpp
    gtestWrapper.h
    integration/test_gcc_project.cpp
)

target_link_libraries(tests_unit
    PRIVATE
        CppBuildInfo
        GTest::GTest
)

target_link_libraries(tests_integration
    PRIVATE
        CppBuildInfo
        GTest::GTest
)

# Configuration file
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/tests_config.h")
target_include_directories(tests_unit  PRIVATE  ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(tests_integration  PRIVATE  ${CMAKE_CURRENT_BINARY_DIR})
