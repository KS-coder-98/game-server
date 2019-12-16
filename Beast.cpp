//
// Created by root on 11/26/19.
//

#include "commonLibray.h"
#include "Beast.h"
#include "server_pthread.h"

Beast::Beast(const struct game *dataGAme) : Character(dataGAme) {
    optionShow = '*';
}

void Beast::move(const struct game *dataGAme, std::mutex * lock) {
    int i = 0;
    int lastChose = 0;
    while (true)
    {
        sem_wait(&sem);
        lock->lock();
        auto temp = dataGAme->mapS;
        if ( lastChose == 0 && (*temp)[position.getY() - 1][position.getX()] != '#'){
            position.setY(position.getY() - 1);
        }
        else if ( lastChose == 1 &&  (*temp)[position.getY() + 1][position.getX()] != '#' ){
            position.setY(position.getY() + 1);
        }
        else if (lastChose == 2 &&  (*temp)[position.getY()][position.getX() + 1] != '#' ){
            position.setX(position.getX() + 1);
        }
        else if (lastChose == 3 &&  (*temp)[position.getY()][position.getX() - 1] != '#' ){
            position.setX(position.getX() - 1);
        }
        else{
            int counter = 0;
            while (true){
                int random = rand() % 4;
                counter++;
                if ( random == 0 && (*temp)[position.getY() - 1][position.getX()] != '#' ){
                    if ( random == lastChose && counter < 30){
                        continue;
                    }
                    position.setY(position.getY() - 1);
                    lastChose = 0;
                    break;
                }
                else if ( random == 1 &&  (*temp)[position.getY() + 1][position.getX()] != '#'){
                    if ( random == lastChose && counter < 30){
                        continue;
                    }
                    position.setY(position.getY() + 1);
                    lastChose = 1;
                    break;
                }
                else if ( random == 2 &&  (*temp)[position.getY()][position.getX() + 1] != '#' ){
                    if ( random == lastChose && counter < 30){
                        continue;
                    }
                    position.setX(position.getX() + 1);
                    lastChose = 2;
                    break;
                }
                else if ( random == 3 &&  (*temp)[position.getY()][position.getX() - 1] != '#'){
                    if ( random == lastChose && counter < 30){
                        continue;
                    }
                    position.setX(position.getX() - 1);
                    lastChose = 3;
                    break;
                }
            }
        }
        i++;
        lock->unlock();
        if (i == -1)
            break;
    }
}
