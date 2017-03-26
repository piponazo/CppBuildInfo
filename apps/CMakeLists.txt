add_subdirectory(cmd)
add_subdirectory(guiGraphicsView)
add_subdirectory(cbiTest)

if (COMPILE_CURSES_APP)
    add_subdirectory(ncurses)
endif()
