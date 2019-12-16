//
// Created by root on 11/28/19.
//

#ifndef GAME_SERVER_MENAGEOFPLAYER_H
#define GAME_SERVER_MENAGEOFPLAYER_H

#include "menageOfPlayer.h"
#include "commonLibray.h"
#include "commonObjects.h"
#include "server_pthread.h"

void joinPlayer(std::mutex *_lock, struct game * dataGame, sem_t * semafor);

#endif //GAME_SERVER_MENAGEOFPLAYER_H
