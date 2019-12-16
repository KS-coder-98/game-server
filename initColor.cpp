//
// Created by root on 11/27/19.
//

#include "initColor.h"



void initColor()
{
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_BLACK, COLOR_RED);
}
