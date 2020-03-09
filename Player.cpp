//
// Created by root on 11/27/19.
//

#include "Player.h"
#include "server_pthread.h"

Player::Player(struct game const* dataGame, pid_t id, char _view, unsigned int _number): Character(dataGame), idPid(id), number(_number) {
    optionShow = _view;
    score = 0;
    keyToQueue = ftok("tmp1", id);
    msgId = msgget(keyToQueue, 0666 | IPC_CREAT);
    deaths = 0;
}

void Player::addPoints(unsigned int value) {
    score+=value;
}

pid_t Player::getIdPid() const {
    return idPid;
}
void Player::movePlayer(const struct game *dataGAme, std::mutex *lock) {
    int counter = 0;
    bool STOPFLAG = true; //zmienić !!!!!!
    std::thread listening(&Player::listenPlayer, this, &STOPFLAG, lock);
    while(counter > -1)
    {
        sem_wait(&sem);
        lock->lock();
        if ( !bufforPlayer.empty() ){
            auto pMap = dataGAme->mapS;
            auto move = bufforPlayer.back();
            bufforPlayer.pop_back();
            if ( move == KEY_UP )
            {
                if ((*pMap)[position.getY() - 1][position.getX()] != WALL){
                    position.setY(position.getY() - 1);
                }
            }
            else if ( move == KEY_DOWN )
            {
                if ((*pMap)[position.getY() + 1][position.getX()] != WALL ){
                    position.setY(position.getY() + 1);
                }
            }
            else if ( move == KEY_RIGHT)
            {
                if ((*pMap)[position.getY()][position.getX() + 1] != WALL ){
                    position.setX(position.getX() + 1);
                }
            }
            else if ( move == KEY_LEFT)
            {
                if ((*pMap)[position.getY()][position.getX() - 1] != WALL ){
                    position.setX(position.getX() - 1);
                }
            }
            else{
//                mvprintw(6, 100, "nic nie pasuje%d!!", counter1++);
            }
        }
        lock->unlock();
        lock->lock();
        msg.mtype = idPid;
        msg.positionX = position.getX();
        msg.positionY = position.getY();
        msg.deaths = this->deaths;
        if ( dataGAme->encampment->findPlayer(this->getIdPid()) != nullptr )
            msg.coinsSecured = dataGAme->encampment->findPlayer(this->getIdPid())->valeu;
        else
            msg.coinsSecured = 0;
        msg.coinsUnSecured = this->getScore();
        msg.numberRound = dataGAme->numberOfRound;
        for ( size_t i = 0; i < 5; i++) // y
        {
            for ( size_t  j = 0; j<5; j++) // x
            {
                msg.map[i][j] = WALL;
                if ( i + position.getY() - 2 >= 0 && i + position.getY() - 2 <  (*dataGAme->mapS).size() && j  + position.getX() - 2 >= 0 && i + position.getY() - 2 <= (*dataGAme->mapS)[0].length()){
                    msg.map[i][j] = (*dataGAme->mapS)[i + position.getY() - 2][j + position.getX() - 2];
                    for ( auto coins : dataGAme->allCoins ){
                        if (coins->getPosition() == Point(j + position.getX() - 2, i + position.getY() - 2) ) {
                            msg.map[i][j] = 'c';
                        }
                    }
                    for ( auto tresure : dataGAme->allTreasure ){
                        if ( tresure->getPosition() == Point(j + position.getX() - 2, i + position.getY() - 2) ) {
                            msg.map[i][j] = 't';
                        }
                    }
                    for ( auto largeTresure : dataGAme->allLargeTreasure ){
                        if ( largeTresure->getPosition() == Point(j + position.getX() - 2, i + position.getY() - 2) ) {
                            msg.map[i][j] = 'T';
                        }
                    }
                    for (auto beast : dataGAme->allBeast){
                        if ( beast->getPosition() ==  Point(j + position.getX() - 2, i + position.getY() - 2) ){
                            msg.map[i][j] = '*';
                        }
                    }
                    for ( auto player : dataGAme->allPlayer ){
                        if ( player->getPosition() ==  Point(j + position.getX() - 2, i + position.getY() - 2)){
                            msg.map[i][j] = player->getNumber() + 1 + '0';
                        }
                    }
                }
//tab[w][c]
// w numer wiersza
// c oznacza numer kolumny
//y = i
            }
        }
        int err = msgsnd(msgId, &msg, sizeof(msg), 0);
        lock->unlock();

    }
}

unsigned int Player::getScore() const {
    return score;
}

void Player::listenPlayer(const bool *flag, std::mutex*lock) {
    while (*flag){
        int temp1 = msgrcv(msgId, &msg, sizeof(msg), idPid * 2, 0);
        mvprintw(25, 100, "!!!!!!!!!!!!!!!!!!!!!!111");
        if ( temp1 != -1 ){
            lock->lock();
            bufforPlayer.push_back(msg.move);
            lock->unlock();
        }
    }
}

void Player::setScore(unsigned int score) {
    Player::score = score;
}

unsigned int Player::getDeaths() const {
    return deaths;
}

void Player::setDeaths(unsigned int deaths) {
    Player::deaths = deaths;
}

unsigned int Player::getNumber() const {
    return number;
}
