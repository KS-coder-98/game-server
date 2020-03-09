//
// Created by root on 11/26/19.
//

#include "Character.h"


void Character::printCharapter(const Map_Window &map) {
    if ( optionShow == '*' )
    {
        attron(COLOR_PAIR(5));
        mvprintw(COORDINATE_Y_PLUS_OFFSET, COORDINATE_X_PLUS_OFFSET, "*");
    }
    else if ( optionShow >= '1' && optionShow <= '4'  )
    {
        attron(COLOR_PAIR(4));
        mvprintw(COORDINATE_Y_PLUS_OFFSET, COORDINATE_X_PLUS_OFFSET, "%c", optionShow);
    }

    else {
        mvprintw(50, 61, "eRRRRRRRRRRRRRRRRRRRRRRRRRRRRR!!!!!!!!!!!!%c", optionShow); //todo information for debug
    }
}

Character::Character(const struct game *dataGame) {
    rewspanPosition.findFreeSpace(dataGame);
    position = rewspanPosition;
    sem_init(&sem, 0, 0);
}

void Character::post() {
    sem_post(&sem);
}

const Point &Character::getPosition() const {
    return position;
}

unsigned int Character::getX() const {
    return position.getX();
}

unsigned int Character::getY() const {
    return position.getY();
}

void Character::setPosition(const Point &position) {
    Character::position = position;
}

const Point &Character::getRewspanPosition() const {
    return rewspanPosition;
}


