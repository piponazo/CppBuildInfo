SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB sources *.cpp)
file(GLOB headers *.h)
file(GLOB uis *.ui)

source_group("Sources" FILES ${sources})
source_group("Headers" FILES ${headers})
source_group("UIs" FILES ${uis})

add_executable(gui ${sources} ${headers} ${uis})

target_link_libraries(gui
    PRIVATE
        Qt5::Widgets
        CppBuildInfo
)
