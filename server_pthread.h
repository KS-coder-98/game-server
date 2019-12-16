//
// Created by root on 11/24/19.
//

#ifndef GAME_SERVER_SERVER_PTHREAD_H
#define GAME_SERVER_SERVER_PTHREAD_H

#define STARTSTATS 100
#define SHIFT 10

#include "commonLibray.h"
#include "commonObjects.h"
#include "initColor.h"


struct game
{
    std::vector<Coins*> all_coins;
    std::vector<Treasure*> all_tresure;
    std::vector<LargeTreasure*>all_large_treasure;
    std::vector<std::string>* mapS;
    std::vector<Beast*> allBeast;
    std::vector<std::thread*>moveBeast;
    std::vector<Player*>allPlayer;
    std::vector<std::thread*>movePlayer;
    std::vector<LeftTreasure*>allLeftTreasure;
    Encampment *encampment;
    pid_t pidServer;
    int flagStart = 0;
    unsigned int numberOfRound = 0;
    int stopFlag = 0;  // when 1 then stop all thread
    unsigned int counterOfPlayer = 0;

};
void add_item(struct game *a, const Map_Window * maze, std::mutex* _lock, int option, sem_t * semagor);
void printAll(struct game *a, const Map_Window & maze, std::mutex* _lock, sem_t * semafor);
void printStats(struct game *dataGame, std::mutex* _lock, sem_t *sem);
void input(std::mutex *_lock, struct game* dataGame, Map_Window * maze, sem_t *semafor);
void collisionDetection(struct game* dataGame, sem_t *sem, std::mutex *lock);
void printBackgroundStats();
void check( Player * player, void * arg );


#endif //GAME_SERVER_SERVER_PTHREAD_H
