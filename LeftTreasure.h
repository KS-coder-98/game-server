//
// Created by root on 12/10/19.
//

#ifndef GAME_SERVER_LEFTTREASURE_H
#define GAME_SERVER_LEFTTREASURE_H

#include "commonLibray.h"
#include "Beneficial_items.h"

class LeftTreasure : public Beneficial_items{
    public:
        LeftTreasure(unsigned int value,const Point &_point);
};




#endif //GAME_SERVER_LEFTTREASURE_H
