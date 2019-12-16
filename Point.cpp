//
// Created by root on 11/26/19.
//

#include "Point.h"
#include "server_pthread.h"

Point::Point(unsigned int x, unsigned int y): x(x), y(y)
{
}

unsigned int Point::getX() const {
    return x;
}

void Point::setX(unsigned int x) {
    Point::x = x;
}

unsigned int Point::getY() const {
    return y;
}

void Point::setY(unsigned int y) {
    Point::y = y;
}

Point::Point(): x(0), y(0)
{
}

void Point::findFreeSpace(struct game const* dataGane) {
    unsigned int tempCoordinate = rand() % (dataGane->mapS->size() - 2) + 1;
    y = tempCoordinate;
    auto temp = dataGane->mapS;
        while (true){
        tempCoordinate = rand() % (  (*temp)[1].length() - 2 ) + 1;
        x = tempCoordinate;
        if ( (*temp)[y][x] != '#' )
            break;
    }
}

bool Point::operator==(const Point &p2) const {
    return x == p2.x && y == p2.y;
}

const Point &Point::getPosition() const {
    return *this;
}

Point::Point(const Point &_point) {
    x = _point.x;
    y = _point.y;
}


