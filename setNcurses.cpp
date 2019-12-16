//
// Created by root on 11/27/19.
//

#include "setNcurses.h"

void setNcurses()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    refresh();
}