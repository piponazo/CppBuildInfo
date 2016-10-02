add_subdirectory(cmd)
add_subdirectory(guiGraphicsView)

if (COMPILE_CURSES_APP)
    add_subdirectory(ncurses)
endif()
