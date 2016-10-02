#include <ncurses.h>

int main() {

    WINDOW *vin;

    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_YELLOW);
    init_pair(3, COLOR_BLUE, COLOR_WHITE);
    vin = newwin(12, 40, 13, 0);
    wmove(vin, 0, 5);
    wprintw(vin, "Hello, World.");
    wbkgd(vin, COLOR_PAIR(1));
    wrefresh(vin);

    getch();
    delwin(vin);
    endwin();

//    raw();
//
//    int derp = 4;
//    printw("This is bog standard string output %d", derp);
//    addch('a');
//    move(12,13);
//
//    mvprintw(15, 20, "Movement");
//
//    getch();
//    endwin();

    return 0;
}
