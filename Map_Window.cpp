//
// Created by root on 11/23/19.
//

#include "Map_Window.h"
#include "commonLibray.h"

Map_Window::Map_Window(const Main_Window & screen, const std::string& nameOfFile)
{
    heigth = screen.get_heigth();
    width = screen.get_width() / 2;
    endX = screen.get_endX() / 2;
    endY = screen.get_endY() - 1;
    startX = screen.get_startX()+5;
    startY = screen.get_startY()+5;
    std::string myText;
    std::ifstream MyReadFile(nameOfFile);
    while (getline (MyReadFile, myText)) {
//        if ( myText[myText.length()-1] == '\n' )
//            myText[myText.length()-1] = '\0';
        mapS.push_back(myText);
    }
    MyReadFile.close();
    bool tempFlag = false;
    for ( size_t y = 0; y < mapS.size(); y++){
        for ( size_t x = 0; x < mapS[y].length(); x++){
            if ( mapS[y][x] == '$' ){
                positionEncampment = Point(x, y);
//                mvprintw(20, 100, "x=%d y=%d", x, y);
                tempFlag = true;
                break;
            }
        }
        if ( tempFlag )
            break;
    }
}

void Map_Window::print_maze() const{
    for (unsigned long i = 0; i < mapS.size(); i++)
    {
        int temp = 0;
        wmove(stdscr, i+startX, startY);
        temp = 0;
        for ( auto a : mapS[i]) {
            temp++;
            if (a == '#') {
                attron(COLOR_PAIR(1));
                printw(" ");
            } else if (a == '$') {
                attron(COLOR_PAIR(3));
                printw("A");
//                this->setPositionEncampment( Point(temp, i) );
                //todo dorobic tu cos z konsturtorem
            } else {
                attron(COLOR_PAIR(2));
                printw(" ");
            }
        }
    }
}

std::vector<std::string> Map_Window::getMaze() const {
    return mapS;
}

std::vector<std::string> *Map_Window::getMazeP() {
    return &mapS;
}

const Point &Map_Window::getPositionEncampment() const {
    return positionEncampment;
}

void Map_Window::setPositionEncampment(const Point &positionEncampment) {
    Map_Window::positionEncampment = positionEncampment;
}


