//
// Created by root on 11/26/19.
//

#ifndef GAME_SERVER_BEAST_H
#define GAME_SERVER_BEAST_H


#include "Character.h"

class Beast: public Character {
    public:
        explicit Beast(struct game const* dataGAme);
        void move(struct game const* dataGAme, std::mutex* lock);
};


#endif //GAME_SERVER_BEAST_H
