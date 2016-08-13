find_program(QT_QMAKE_EXECUTABLE NAMES qmake-qt5)
find_package(Qt5Core REQUIRED)

if (${Qt5Core_VERSION} VERSION_LESS 5.7)
    message(FATAL_ERROR "CppBuildInfo requires at least Qt 5.7. Version found: ${Qt5Core_VERSION}")
endif ()
