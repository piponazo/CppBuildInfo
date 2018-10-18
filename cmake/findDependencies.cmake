if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

find_package(Qt5Core    CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG)

find_package(Curses)

if (COMPILE_TESTS)
    find_package(GTest REQUIRED)
endif()

set(CMAKE_INSTALL_RPATH ${CMAKE_PREFIX_PATH}/lib)
