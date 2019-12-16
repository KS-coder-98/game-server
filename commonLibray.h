//
// Created by root on 11/27/19.
//

#ifndef GAME_SERVER_COMMONLIBRAY_H
#define GAME_SERVER_COMMONLIBRAY_H

#include <ncurses.h>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <fstream>
#include <sys/msg.h>
#include <semaphore.h>


struct MassageJoin
{
    long mtype;
    pid_t pid;
};

#endif //GAME_SERVER_COMMONLIBRAY_H
