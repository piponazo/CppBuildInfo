find_program(QT_QMAKE_EXECUTABLE NAMES qmake-qt5)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

if (${Qt5Core_VERSION} VERSION_LESS 5.6)
    message(FATAL_ERROR "CppBuildInfo requires at least Qt 5.6. Version found: ${Qt5Core_VERSION}")
endif ()

if (COMPILE_TESTS)
    add_subdirectory(${CMAKE_SOURCE_DIR}/cmake/ext/gtest)
endif()

set(CMAKE_INSTALL_RPATH ${CMAKE_PREFIX_PATH}/lib)
