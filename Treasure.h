//
// Created by root on 11/24/19.
//

#ifndef GAME_SERVER_TREASURE_H
#define GAME_SERVER_TREASURE_H


#include "Beneficial_items.h"

class Treasure : public Beneficial_items {
    public:
        explicit Treasure(const Map_Window & map);
        explicit Treasure(const struct game *dataGame);
};


#endif //GAME_SERVER_TREASURE_H
