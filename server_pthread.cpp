//
// Created by root on 11/24/19.
//

#include "server_pthread.h"

void add_item(struct game *a, const Map_Window * maze, std::mutex* _lock, int optionAdd)
{
    if ( optionAdd == 'c' )
    {
        a->all_coins.push_back(new Coins(a));
        mvprintw(50, 30, "||||_%d_!!!!!!!!!!!!", a->all_coins.size());
    }
    else if ( optionAdd == 't')
    {
        a->all_tresure.push_back(new Treasure(a));
    }
    else if ( optionAdd == 'T' )
    {
        a->all_large_treasure.push_back(new LargeTreasure(a));
    }
    else if ( optionAdd == 'b' )
    {
        a->allBeast.push_back(new Beast(a));
        a->moveBeast.push_back( new std::thread(&Beast::move, a->allBeast.back(), a, _lock) );
    }

}

void printAll(struct game *a, const Map_Window & maze, std::mutex* _lock, sem_t * semafor)
{
    while (a->stopFlag != 1){
        sem_wait(semafor);
        _lock->lock();
        maze.print_maze();
        for ( auto i : a->all_coins ) {
            i->print_item(1, maze);
        }
        for (auto i : a->all_large_treasure) {
            i->print_item(3, maze);
        }
        for (auto i : a->all_tresure) {
            i->print_item(2, maze);
        }
        for (auto i : a->allLeftTreasure )
            i->print_item(4 ,maze);
        for(auto i : a->allPlayer){
            i->printCharapter(maze);
        }
        for (auto i : a->allBeast) {
            i->printCharapter(maze);
        }
        refresh();
        _lock->unlock();
    }
}

void input(std::mutex *_lock, struct game* dataGame, Map_Window * maze, sem_t *semafor)
{
    int option = ' ';
    while ( option != 'e' ){
        sem_wait(semafor);
        option = getch();
        _lock->lock();
        if ( option != -1)
            add_item(dataGame, maze, _lock, option);
        if ( 'e' == option )
            dataGame->stopFlag = 1;
        mvprintw(1, 0, "wyszlo");
        refresh();
        _lock->unlock();
    }
}

void printStats(struct game *dataGame, std::mutex* _lock, sem_t *sem)//dorobic semafor
{
    _lock->lock();
    printBackgroundStats();
    int i = 0;
    _lock->unlock();
    while ( dataGame->stopFlag != 1 ){
        sem_wait(sem);
        _lock->lock();
        printBackgroundStats();
        i = 0;
        mvprintw(1, STARTSTATS, "Server pid's %u", dataGame->pidServer);
        mvprintw(2, STARTSTATS, "Campsite X/Y %d/%d", dataGame->encampment->getPosition().getX(), dataGame->encampment->getPosition().getY());
        mvprintw(3, STARTSTATS, "Round number %d", dataGame->numberOfRound);
        for ( auto player = std::begin(dataGame->allPlayer); player != std::end(dataGame->allPlayer); player++, i++ ){
            mvprintw(5, STARTSTATS + SHIFT + (1+i)*10, "Player %d", (*player)->getNumber() + 1);
            mvprintw(6, STARTSTATS + SHIFT + (1+i)*10, "%d", (*player)->getIdPid());
            mvprintw(7, STARTSTATS + SHIFT + (1+i)*10, "type" );
            mvprintw(8, STARTSTATS + SHIFT + (1+i)*10, "%d/%d", (*player)->getX(), (*player)->getY());
            mvprintw(9, STARTSTATS + SHIFT + (1+i)*10, "%u", (*player)->getDeaths());
            mvprintw(13, STARTSTATS + SHIFT + (1+i)*10, "%u", (*player)->getScore());
            auto temp = dataGame->encampment->findPlayer( (*player)->getIdPid() );
            if ( temp != nullptr )
                mvprintw(14, STARTSTATS + SHIFT + (1+i)*10, "%u", (*temp).valeu);
            else
                mvprintw(14, STARTSTATS + SHIFT + (1+i)*10, "0");

        }
        _lock->unlock();
    }
}


void collisionDetection(struct game* dataGame, sem_t *sem, std::mutex *lock) {
    auto coins = std::begin(dataGame->all_coins);
    auto player = std::begin(dataGame->allPlayer);
    auto tresure = std::begin(dataGame->all_tresure);
    auto largeTresure = std::begin(dataGame->all_large_treasure);
    auto leftTreasure = std::begin(dataGame->allLeftTreasure);
    auto beast = std::begin(dataGame->allBeast);
    while (dataGame->stopFlag != 1) {
        sem_wait(sem);
        lock->lock();
        // test coins
        player = std::begin(dataGame->allPlayer);
        while (player != std::end(dataGame->allPlayer)) {
            coins = std::begin(dataGame->all_coins);
            while (coins != std::end(dataGame->all_coins)) {
                if ((*coins)->getPosition() == (*player)->getPosition()) {
                    (*player)->addPoints(1);
                    dataGame->all_coins.erase(coins);
                    continue;
                }
                coins++;
            }
            player++;
        }
        //test treasure
        player = std::begin(dataGame->allPlayer);
        while (player != std::end(dataGame->allPlayer)) {
            tresure = std::begin(dataGame->all_tresure);
            while (tresure != std::end(dataGame->all_tresure)) {
                if ((*tresure)->getPosition() == (*player)->getPosition()) {
                    (*player)->addPoints((*tresure)->getValue());
                    dataGame->all_tresure.erase(tresure);
                    continue;
                }
                tresure++;
            }
            player++;
        }
        //test largetreasure
        player = std::begin(dataGame->allPlayer);
        while (player != std::end(dataGame->allPlayer)) {
            largeTresure = std::begin(dataGame->all_large_treasure);
            while (largeTresure != std::end(dataGame->all_large_treasure)) {
                if ((*largeTresure)->getPosition() == (*player)->getPosition()) {
                    (*player)->addPoints((*largeTresure)->getValue());
                    dataGame->all_large_treasure.erase(largeTresure);
                    continue;
                }
                largeTresure++;
            }
            player++;
        }
        //test lefttreasure
        player = std::begin(dataGame->allPlayer);
        while (player != std::end(dataGame->allPlayer)) {
            leftTreasure = std::begin(dataGame->allLeftTreasure);
            while (leftTreasure != std::end(dataGame->allLeftTreasure)) {
                if ((*leftTreasure)->getPosition() == (*player)->getPosition()) {
                    (*player)->addPoints((*leftTreasure)->getValue());
                    dataGame->allLeftTreasure.erase(leftTreasure);
                    continue;
                }
                leftTreasure++;
            }
            player++;
        }
        //test beast
        player = std::begin(dataGame->allPlayer);
        bool tempFlag = false;
        while (player != std::end(dataGame->allPlayer)) {
            beast = std::begin(dataGame->allBeast);
            while (beast != std::end(dataGame->allBeast)) {
                if ((*beast)->getPosition() == (*player)->getPosition()) {
                    dataGame->allLeftTreasure.push_back(new LeftTreasure((*player)->getScore(), (*player)->getPosition() ));
                    (*player)->setPosition((*player)->getRewspanPosition());
                    (*player)->setScore(0);
                    (*player)->setDeaths((*player)->getDeaths() + 1);
                    tempFlag = true;
                    break;
                    //todo zostawienie skarbu
                }
                if ( tempFlag == true )
                    break;
                beast++;
            }
            player++;
        }
        //test player with player
        player = std::begin(dataGame->allPlayer);
        while ( player != std::end(dataGame->allPlayer) ){
            auto playerComper = std::begin((dataGame->allPlayer));
            while ( playerComper != std::end(dataGame->allPlayer) ) {
                if (playerComper == player)
                    break;
                if ((*player)->getPosition() == (*playerComper)->getPosition()) {
                    dataGame->allLeftTreasure.push_back(
                            new LeftTreasure((*player)->getScore() + (*playerComper)->getScore(),
                                             (*player)->getPosition()));
                    (*player)->setScore(0);
                    (*playerComper)->setScore(0);
                    (*player)->setPosition((*player)->getRewspanPosition());
                    (*playerComper)->setPosition((*playerComper)->getRewspanPosition());
                    (*player)->setDeaths((*player)->getDeaths() + 1);
                    (*playerComper)->setDeaths((*playerComper)->getDeaths() + 1);
                }
                playerComper++;
            }
            player++;
        }
        player = std::begin(dataGame->allPlayer);
        while ( player != std::end( dataGame->allPlayer ) ){
            if ( (*player)->getPosition() == dataGame->encampment->getPosition() ){
                mvprintw( 21, STARTSTATS, "jest w obozie");
                (*dataGame->encampment).putOutTreasure(**player);
            }
            player++;
        }
        lock->unlock();
    }
}


void printBackgroundStats() {
    attron(COLOR_PAIR(2));
    for (size_t i = 1; i < 20; i++){
        for ( size_t j = 0; j < 60; j++){
            mvprintw(i, STARTSTATS + j, " ");
        }
    }
    mvprintw(5, STARTSTATS, "Parametr: ");
    mvprintw(6, STARTSTATS, "Pid: ");
    mvprintw(7, STARTSTATS, "Type: ");
    mvprintw(8, STARTSTATS, "Curr X/Y: ");
    mvprintw(9, STARTSTATS, "Deaths");
    mvprintw(12, STARTSTATS, "Coins");
    mvprintw(13, STARTSTATS + 1, "Unsecured");
    mvprintw(14, STARTSTATS + 1, "Secured");
}











//        while ( player != std::end(dataGame->allPlayer) ){
//            lock->lock();
//            coins = std::begin(dataGame->all_coins);
//            tresure = std::begin(dataGame->all_tresure);
//            largeTresure = std::begin(dataGame->all_large_treasure);
//            leftTreasure = std::begin(dataGame->allLeftTreasure);
//            beast = std::begin(dataGame->allBeast);
//            while ( coins != std::end(dataGame->all_coins)){
//                if ( (*coins)->getPosition() == (*player)->getPosition() ){
//                    (*player)->addPoints(1);
//                    dataGame->all_coins.erase(coins);
//                    continue;
//                }
//                coins++;
//            }
//            while ( tresure != std::end(dataGame->all_tresure)){
//                if ( (*tresure)->getPosition() == (*player)->getPosition() ){
//                    (*player)->addPoints((*tresure)->getValue());
//                    dataGame->all_tresure.erase(tresure);
//                    continue;
//                }
//                tresure++;
//            }
//            while ( largeTresure != std::end(dataGame->all_large_treasure)){
//                if ( (*largeTresure)->getPosition() == (*player)->getPosition() ){
//                    (*player)->addPoints((*largeTresure)->getValue());
//                    dataGame->all_large_treasure.erase(largeTresure);
//                    continue;
//                }
//                largeTresure++;
//            }
//            while ( leftTreasure != std::end(dataGame->allLeftTreasure) ){
//                if ( (*leftTreasure)->getPosition() == (*player)->getPosition() ){
//                    (*player)->addPoints( (*leftTreasure)->getValue() );
//                    dataGame->allLeftTreasure.erase(leftTreasure);
//                    continue;
//                }
//                leftTreasure++;
//            }
//            while ( beast != std::end(dataGame->allBeast)){
//                if ( (*beast)->getPosition() == (*player)->getPosition() ){
//                    dataGame->allLeftTreasure.push_back(new LeftTreasure( (*player)->getScore(), (*player)->getPosition() ) );
//                    (*player)->setPosition((*player)->getRewspanPosition());
//                    (*player)->setScore(0);
//                    (*player)->setDeaths((*player)->getDeaths()+1);
//                    break;
//                    //todo zostawienie skarbu
//                }
//                beast++;
//            }
//            player++;
//            lock->unlock();
//        }




