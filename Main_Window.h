//
// Created by root on 11/21/19.
//

#ifndef GAME_SERVER_MAIN_WINDOW_H
#define GAME_SERVER_MAIN_WINDOW_H



class Main_Window {
    protected:
        unsigned int width;
        unsigned int heigth;
public:
    unsigned int getWidth() const;

    void setWidth(unsigned int width);

    unsigned int getHeigth() const;

    void setHeigth(unsigned int heigth);

    unsigned int getEndX() const;

    void setEndX(unsigned int endX);

    unsigned int getEndY() const;

    void setEndY(unsigned int endY);

    unsigned int getStartX() const;

    void setStartX(unsigned int startX);

    unsigned int getStartY() const;

    void setStartY(unsigned int startY);

protected:
    unsigned int endX;
        unsigned int endY;
        unsigned int startX;
        unsigned int startY;
    public:
        Main_Window();
        [[nodiscard]] unsigned int get_heigth() const;
        [[nodiscard]] unsigned int get_width() const;
        [[nodiscard]] unsigned int get_endX() const;
        [[nodiscard]] unsigned int get_endY() const;
        [[nodiscard]] unsigned int get_startX() const;
        [[nodiscard]] unsigned int get_startY() const;
        void paint();
        virtual ~Main_Window();
};


#endif //GAME_SERVER_MAIN_WINDOW_H
