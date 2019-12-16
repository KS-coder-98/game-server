#include "Main_Window.h"
#include "Map_Window.h"
#include "Treasure.h"
#include "LargeTreasure.h"
#include "Coins.h"
//#include <thread>
#include "initColor.h"
#include "setNcurses.h"
#include "server_pthread.h"
#define MAP "mapa.txt"
#include "commonLibray.h"
#include "menageOfPlayer.h"



int main() {
    std::mutex lockPrint;
    std::mutex lockData;
    srand(time(NULL));

    // intialize ncuses cursor etc
    setNcurses();

    // inicialize color consolle
    initColor();


    // declarate variable object etc
    Main_Window view;
    view.paint();
    Map_Window maze(view, MAP);
    maze.print_maze();
    game game_object;
    game_object.pidServer = getpid();
    game_object.mapS = maze.getMazeP();
    Encampment encampment(maze.getPositionEncampment());
    game_object.encampment = &encampment;
    sem_t semInput;
    sem_t semJoinPlayer;
    sem_t semPrint;
    sem_t semPrintStat;
    sem_t semColisionDetectet;
    sem_init(&semPrintStat, 0 ,0);
    sem_init(&semInput, 0, 0);
    sem_init(&semPrint, 0, 0);
    sem_init(&semJoinPlayer, 0, 0);
    sem_init(&semColisionDetectet, 0, 0);
    std::thread printStatsThread(printStats, &game_object, &lockPrint, &semPrintStat);
    std::thread inputThread(input, &lockPrint, &game_object, &maze, &semInput);
    std::thread tMenagmentPlayer(joinPlayer, &lockPrint, &game_object, &semJoinPlayer);
    std::thread ptrintThread(printAll, &game_object, maze, &lockPrint, &semPrint);
    std::thread threadDetectionColision(collisionDetection, &game_object, &semColisionDetectet, &lockPrint);

    while(game_object.stopFlag != 1)
    {
        if ( game_object.flagStart == 1 ){ // tu treba dorobić flage
            game_object.numberOfRound++;
            for ( auto beast : game_object.allBeast )
                beast->post();
            for (auto player : game_object.allPlayer)
                player->post();
        }
        sem_post(&semInput); // dla watku od wczytywania znaku
        sem_post(&semJoinPlayer);
        sem_post(&semPrintStat);
        usleep(100000);
        sem_post(&semColisionDetectet);
        usleep(400000);
        sem_post(&semPrint);
        usleep(500000);
    }

    //close all staff



    refresh();
    getch(); //3
    endwin(); //4
    return 0;
}