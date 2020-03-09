//
// Created by root on 11/26/19.
//

#ifndef GAME_SERVER_BEAST_H
#define GAME_SERVER_BEAST_H

#define REPEATABILITY_FACTOR 30

#define DOWN 0

#define UP 1

#define RIGHT 2

#define LEFT 3

#define TRY_AGAIN random == lastChose && counter < REPEATABILITY_FACTOR

#include "Character.h"

class Beast: public Character {
    public:
        explicit Beast(struct game const* dataGame);
        void move(struct game const* dataGame, std::mutex* lock);
};


#endif //GAME_SERVER_BEAST_H
