add_executable(tests
    main.cpp
    gtestWrapper.h
    unit/test_DataParser.cpp
    unit/test_CompilationProcess.cpp
    unit/test_utils.cpp
)


target_link_libraries(tests
    PRIVATE
        CppBuildInfo
        GTest::GTest
)

# Configuration file
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/tests_config.h")
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}) # For detecting tests_config.h
