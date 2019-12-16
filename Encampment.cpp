//
// Created by root on 12/11/19.
//

#include "Encampment.h"

Encampment::Encampment(const Point & point): position(point) {

}

void Encampment::putOutTreasure(Player &_player) {
    bool exist = false;
    for ( auto p = std::begin(Encampment::players); p != std::end(Encampment::players); p++ ){
        if ( (*p)->id == _player.getIdPid() ){
            mvprintw(22, 130, "znalzlo juz obiekt");
            exist = true;
            (*p)->valeu += _player.getScore();
            break;
        }
    }
    if (!exist){
        mvprintw(20, 110, "%d %d", _player.getIdPid(), _player.getScore());
//        Encampment::players.emplace_back(_player.getIdPid(), _player.getScore() );
        Encampment::players.push_back(new player(_player.getIdPid(), _player.getScore()));
    }
    _player.setScore(0);
    for ( size_t i = 0; i < players.size(); i++){
        mvprintw(21 + i, 100 , "wielkows = %d i = %dpid = %d !%d!",players.size(), i,  Encampment::players[i]->id, Encampment::players[i]->valeu);
    }
}

const Point &Encampment::getPosition() const {
    return position;
}

const struct Encampment::player *Encampment::findPlayer(pid_t pid) const {
    for ( auto item : players ){
        if ( item->id == pid )
            return item;
    }
    return nullptr;
}



Encampment::player::player(pid_t _id, unsigned int _value): id(_id), valeu(_value) {

}
