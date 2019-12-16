//
// Created by root on 11/26/19.
//

#ifndef GAME_SERVER_POINT_H
#define GAME_SERVER_POINT_H

#include "commonLibray.h"



class Point {
        unsigned int x;
        unsigned int y;
    public:
        Point();
        Point(unsigned int x, unsigned int y);
        Point(const Point &_point );
        bool operator ==(const Point &p2) const;
        [[nodiscard]] const Point &getPosition() const;
        [[nodiscard]] unsigned int getX() const;

        void setX(unsigned int x);

        [[nodiscard]] unsigned int getY() const;

        void setY(unsigned int y);

        void findFreeSpace(struct game const*);

        bool isFree(struct game const *);
};

#endif //GAME_SERVER_POINT_H
