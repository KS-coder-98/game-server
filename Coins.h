//
// Created by root on 11/24/19.
//

#ifndef GAME_SERVER_COINS_H
#define GAME_SERVER_COINS_H

#include "commonLibray.h"
#include "Beneficial_items.h"

class Coins : public Beneficial_items {
    public:
        explicit Coins(const Map_Window & map);
        explicit Coins(const struct game *dataGame);
};


#endif //GAME_SERVER_COINS_H
