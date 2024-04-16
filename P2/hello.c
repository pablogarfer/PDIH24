// gcc hello.c -o hello -lncurses

#include <ncurses.h>
#include <stdio.h>
int main() {
    initscr();
    printw("Holita!");
    refresh();
    getch();
    endwin();
return 0;
}

