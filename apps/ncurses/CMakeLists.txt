if (NOT CURSES_FOUND)
    message(FATAL_ERROR "ncurses library not found")
endif()

add_executable(cbi_curses main.c)
target_link_libraries(cbi_curses ${CURSES_NCURSES_LIBRARY})
