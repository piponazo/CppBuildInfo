SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB sources *.cpp)
file(GLOB headers *.hpp)
file(GLOB uis *.ui)

add_executable(gui2 ${sources} ${headers} ${uis})

target_link_libraries(gui2 Qt5::Widgets CppBuildInfo)
