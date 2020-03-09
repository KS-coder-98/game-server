//
// Created by root on 11/26/19.
//

#include "commonLibray.h"
#include "Beast.h"
#include "server_pthread.h"

Beast::Beast(const struct game *dataGame) : Character(dataGame) {
    optionShow = '*';
}

void Beast::move(const struct game *dataGame, std::mutex * lock) {
    int lastChose = DOWN;
    while (dataGame->stopFlag != STOP_VALUE)
    {
        sem_wait(&sem);
        lock->lock();
        auto temp = dataGame->mapS;
        if ( lastChose == DOWN && (*temp)[position.getY() - 1][position.getX()] != WALL){
            position.setY(position.getY() - 1);
        }
        else if ( lastChose == UP &&  (*temp)[position.getY() + 1][position.getX()] != WALL ){
            position.setY(position.getY() + 1);
        }
        else if (lastChose == RIGHT &&  (*temp)[position.getY()][position.getX() + 1] != WALL ){
            position.setX(position.getX() + 1);
        }
        else if (lastChose == LEFT &&  (*temp)[position.getY()][position.getX() - 1] != WALL ){
            position.setX(position.getX() - 1);
        }
        else{
            int counter = DOWN;
            while (true){
                int random = rand() % 4;
                counter++;
                if ( random == DOWN && (*temp)[position.getY() - 1][position.getX()] != WALL ){
                    if ( TRY_AGAIN){
                        continue;
                    }
                    position.setY(position.getY() - 1);
                    lastChose = DOWN;
                    break;
                }
                else if ( random == UP &&  (*temp)[position.getY() + 1][position.getX()] != WALL){
                    if ( TRY_AGAIN){
                        continue;
                    }
                    position.setY(position.getY() + 1);
                    lastChose = UP;
                    break;
                }
                else if ( random == RIGHT &&  (*temp)[position.getY()][position.getX() + 1] != WALL ){
                    if ( TRY_AGAIN){
                        continue;
                    }
                    position.setX(position.getX() + 1);
                    lastChose = RIGHT;
                    break;
                }
                else if ( random == LEFT &&  (*temp)[position.getY()][position.getX() - 1] != WALL){
                    if ( TRY_AGAIN){
                        continue;
                    }
                    position.setX(position.getX() - 1);
                    lastChose = LEFT;
                    break;
                }
            }
        }
        lock->unlock();
    }
}
