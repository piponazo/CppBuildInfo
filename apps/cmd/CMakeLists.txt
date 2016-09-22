add_executable(cbi main.cpp)
target_link_libraries(cbi Qt4::QtCore)

install(TARGETS cbi RUNTIME DESTINATION bin)
