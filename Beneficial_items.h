//
// Created by root on 11/24/19.
//

#ifndef GAME_SERVER_BENEFICIAL_ITEMS_H
#define GAME_SERVER_BENEFICIAL_ITEMS_H

#include "Map_Window.h"
#include "Point.h"
#include "commonLibray.h"
#include "CONST_AND_DEFINE.h"
#define COINS 1
#define TREASURE 2
#define LARGE_TREASURE 3
#define LEFT_TREASURE 4

#define COINS_SIGN "C"

#define TREASURE_SIGN "t"

#define LARGE_TREASURE_SIGN "T"

#define LEFT_TREASURE_SIGN "D"



class Beneficial_items {
    protected:
        unsigned int value;
        Point position;
    public:
        unsigned int getValue() const;
        const Point &getPosition() const;
        explicit Beneficial_items(const Map_Window &map);
        explicit Beneficial_items(struct game const* dataGame);
        explicit Beneficial_items(const Point & point);
        Beneficial_items(unsigned int x, unsigned int y);
        void print_item(int option, const Map_Window & map);
};


#endif //GAME_SERVER_BENEFICIAL_ITEMS_H
