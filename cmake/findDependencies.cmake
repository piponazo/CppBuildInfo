find_package(Qt4 COMPONENTS QtGui QtCore REQUIRED)
find_package(Curses)

if (COMPILE_TESTS)
    find_package(GTest)
endif()

set(CMAKE_INSTALL_RPATH ${CMAKE_PREFIX_PATH}/lib)
