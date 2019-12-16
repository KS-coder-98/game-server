//
// Created by root on 11/26/19.
//

#ifndef GAME_SERVER_CHARACTER_H
#define GAME_SERVER_CHARACTER_H

#include "Map_Window.h"
#include "Point.h"
#include "commonLibray.h"

#define BEAST 1
#define PLAYER 2


class Character {
    public:
        explicit Character(struct game const* dataGame);
        void printCharapter(const Map_Window & map);
        void post();
        [[nodiscard]] const Point &getPosition() const;
        [[nodiscard]] unsigned int getX() const;
        [[nodiscard]] unsigned int getY() const;
        void setPosition(const Point &position);
        const Point &getRewspanPosition() const;

protected:
    Point position;
    Point rewspanPosition;
    char optionShow;
    sem_t sem;
};


#endif //GAME_SERVER_CHARACTER_H
