//
// Created by root on 12/11/19.
//

#ifndef GAME_SERVER_ENCAMPMENT_H
#define GAME_SERVER_ENCAMPMENT_H


#include <termio.h>
#include "commonObjects.h"
#include "commonLibray.h"
//#include <vector>

class Encampment {
    Point position;
    struct player;
    std::vector<struct player*>players;

public:
    explicit Encampment(const Point & point);
    void putOutTreasure(Player &_player);
    const Point &getPosition() const;
    const struct player* findPlayer(pid_t pid) const;
};

struct Encampment::player {
    pid_t id;
    unsigned int valeu;
    player(pid_t _id, unsigned int _value);
};




#endif //GAME_SERVER_ENCAMPMENT_H
