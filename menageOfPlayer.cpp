//
// Created by root on 11/28/19.
//

#include <csignal>
#include "menageOfPlayer.h"


struct MassageServer
{
    long mtype;
    pid_t pid;
    bool ok;
};



void joinPlayer(std::mutex *_lock, struct game* dataGame, sem_t * semafor)
{
    MassageJoin msgJoin;
    key_t keyJoin = ftok("tmp", 150);
    int msgIdJoin = msgget(keyJoin, 0666 | IPC_CREAT);
    while ( dataGame->stopFlag != 1 ){
        sem_wait(semafor);
        int err = msgrcv(msgIdJoin, &msgJoin, sizeof(MassageJoin), 5, IPC_NOWAIT);
        _lock->lock();
        if ( err != -1 ){
            if ( dataGame->counterOfPlayer < 4 ) {
                int temp = dataGame->allPlayer.size() + 1;
                dataGame->allPlayer.push_back(new Player(dataGame, msgJoin.pid, temp + '0', dataGame->counterOfPlayer));
                dataGame->movePlayer.push_back(new std::thread(&Player::movePlayer, dataGame->allPlayer.back(), dataGame, _lock));
                dataGame->counterOfPlayer++;
            }
            else{
//                pid_t idPid = msgJoin.pid;
//                key_t keyToQueue = ftok("tmp1", idPid);
//                int msgId;
//                struct Massge msg;
//                msg.mtype = idPid;
//                msg.mtype = idPid;
//                msg.move = -10;
//                msg.pid_ = idPid;
//
//                msgId = msgget(keyToQueue, 0666);
//                int err = msgsnd(msgqid, &msg, sizeof(msg), 0);
//                break;
            }
            if ( dataGame->counterOfPlayer == 4 && dataGame->flagStart != 1){
                dataGame->flagStart = 1;
            }
        }
        for (size_t i = 0; i < dataGame->allPlayer.size(); i++){
            if ( kill( dataGame->allPlayer[i]->getIdPid(), 0) != 0  ){
                dataGame->allPlayer.erase(dataGame->allPlayer.begin() + i);
                dataGame->counterOfPlayer--;
                break;
            }
        }
        _lock->unlock();
    }
}
