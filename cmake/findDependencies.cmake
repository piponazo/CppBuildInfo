find_package(Qt4 COMPONENTS QtGui QtCore REQUIRED)
find_package(Curses)

if (COMPILE_TESTS)
    add_subdirectory(${CMAKE_SOURCE_DIR}/cmake/ext/gtest)
endif()

set(CMAKE_INSTALL_RPATH ${CMAKE_PREFIX_PATH}/lib)
