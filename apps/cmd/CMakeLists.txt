add_executable(cbi main.cpp)
target_link_libraries(cbi PRIVATE CppBuildInfo)

install(TARGETS cbi RUNTIME DESTINATION bin)
