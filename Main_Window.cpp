//
// Created by root on 11/21/19.
//


#include "Main_Window.h"
#include "commonLibray.h"


Main_Window::Main_Window()
{
    getmaxyx(stdscr, heigth, width);
    endX = width - 1;
    endY = heigth - 1;
    startY = 0;
    startX = 0;
};

unsigned int Main_Window::get_heigth() const{
    return heigth;
}
unsigned int Main_Window::get_width() const
{
    return width;
};
unsigned int Main_Window::get_endX() const
{
    return endX;
};
unsigned int Main_Window::get_endY() const
{
    return endY;
}
unsigned int Main_Window::get_startX() const
{
    return startX;
};
unsigned int Main_Window::get_startY() const
{
    return startY;
};

Main_Window::~Main_Window()
{};

void Main_Window::paint() {
    for ( size_t i = 0; i < width; i++)
    {
        for ( size_t i = 0; i < heigth; i++)
        {
            attron(COLOR_PAIR(3));
            printw(" ");
        }
    }
    for ( size_t i = 0; i < heigth; i++)
    {
        attron(COLOR_PAIR(2));
        mvprintw(i, width/2-1, "   ");
    }
}

unsigned int Main_Window::getWidth() const {
    return width;
}

void Main_Window::setWidth(unsigned int width) {
    Main_Window::width = width;
}

unsigned int Main_Window::getHeigth() const {
    return heigth;
}

void Main_Window::setHeigth(unsigned int heigth) {
    Main_Window::heigth = heigth;
}

unsigned int Main_Window::getEndX() const {
    return endX;
}

void Main_Window::setEndX(unsigned int endX) {
    Main_Window::endX = endX;
}

unsigned int Main_Window::getEndY() const {
    return endY;
}

void Main_Window::setEndY(unsigned int endY) {
    Main_Window::endY = endY;
}

unsigned int Main_Window::getStartX() const {
    return startX;
}

void Main_Window::setStartX(unsigned int startX) {
    Main_Window::startX = startX;
}

unsigned int Main_Window::getStartY() const {
    return startY;
}

void Main_Window::setStartY(unsigned int startY) {
    Main_Window::startY = startY;
}
