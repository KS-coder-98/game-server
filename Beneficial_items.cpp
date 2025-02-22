//
// Created by root on 11/24/19.
//
#include "ncurses.h"

#include "Beneficial_items.h"
#include <cstdlib>

Beneficial_items::Beneficial_items(const Map_Window & map)
{
    unsigned int tempCoordinate = rand() % (map.getMaze().size() - 2) + 1;
    position.setY(tempCoordinate);
        mvprintw(14, 100, "wysokosc = %d szerokosc = %d", map.getMaze().size(),  map.getMaze()[1].length()); //todo debug need this line
    auto temp = map.getMaze();
    while (true){
        tempCoordinate = rand() % (map.getMaze()[1].length() - 2) + 1;
        position.setX(tempCoordinate);
        if ( temp[position.getY()][position.getX()] != WALL )
            break;
    }
}


void Beneficial_items::print_item(int option, const Map_Window & map) {
    attron(COLOR_PAIR(4));
    if ( option == COINS )
    {
        mvprintw(COORDINATE_Y_PLUS_OFFSET, COORDINATE_X_PLUS_OFFSET, COINS_SIGN);
    }
    else if ( option == TREASURE )
    {
        mvprintw(COORDINATE_Y_PLUS_OFFSET, COORDINATE_X_PLUS_OFFSET, TREASURE_SIGN);
    }
    else if (option == LARGE_TREASURE )
    {
        mvprintw(COORDINATE_Y_PLUS_OFFSET, COORDINATE_X_PLUS_OFFSET, LARGE_TREASURE_SIGN);
    }
    else if ( option == LEFT_TREASURE )
    {
        mvprintw(COORDINATE_Y_PLUS_OFFSET, COORDINATE_X_PLUS_OFFSET, LEFT_TREASURE_SIGN);
    }
    else
        mvprintw(5, 5, "erroro in file beneficial_items.cpp "); //todo information for debug
}

Beneficial_items::Beneficial_items(const struct game *dataGame) {
    position.findFreeSpace(dataGame);
}

const Point &Beneficial_items::getPosition() const {
    return position;
}

unsigned int Beneficial_items::getValue() const {
    return value;
}

Beneficial_items::Beneficial_items(const Point &_point): position(_point) {
    value =0;
}

Beneficial_items::Beneficial_items(unsigned int x, unsigned int y): position(x, y) {

}



