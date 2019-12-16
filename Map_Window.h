//
// Created by root on 11/23/19.
//

#ifndef GAME_SERVER_MAP_WINDOW_H
#define GAME_SERVER_MAP_WINDOW_H


#include <string>
#include <vector>
#include "Point.h"
#include "Main_Window.h"


class Map_Window: public Main_Window {
    protected:
        std::vector<std::string> mapS;
        Point positionEncampment;
    public:
    void setPositionEncampment(const Point &positionEncampment);

    Map_Window(const Main_Window & screen, const std::string& nameOfFile);
        void print_maze() const;
        [[nodiscard]] const Point &getPositionEncampment() const;

    [[nodiscard]] std::vector<std::string> getMaze() const;
    [[nodiscard]] std::vector<std::string> *getMazeP();
};


#endif //GAME_SERVER_MAP_WINDOW_H
