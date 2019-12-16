//
// Created by root on 11/24/19.
//

#ifndef GAME_SERVER_LARGETREASURE_H
#define GAME_SERVER_LARGETREASURE_H


#include "Beneficial_items.h"


class LargeTreasure: public Beneficial_items {
    public:
        explicit LargeTreasure(const Map_Window & map);
        explicit LargeTreasure(const struct game *dataGame);
};


#endif //GAME_SERVER_LARGETREASURE_H
