//
// Created by root on 11/27/19.
//

#ifndef GAME_SERVER_PLAYER_H
#define GAME_SERVER_PLAYER_H

#define UP 1
#define  DOWN 2
#define  LEFT 3
#define RAIGHT 4

#include "Character.h"

struct Massge{
    long mtype;
    int move;
    pid_t pid_;
    char map[5][5];

    pid_t pidServer;
    unsigned int numberRound;
    unsigned int numberPlayer;
    std::string type;
    unsigned int deaths;
    unsigned int coinsSecured;
    unsigned int coinsUnSecured;
    unsigned int positionX;
    unsigned int positionY;
};

class Player : public Character{
    unsigned int score;
    pid_t idPid;
    key_t keyToQueue;
    unsigned int number;
    int msgId;
    struct Massge msg;
public:
    unsigned int getNumber() const;

private:
    unsigned int deaths;
    std::vector<int> bufforPlayer;
public:
    unsigned int getDeaths() const;
    void setDeaths(unsigned int deaths);
    pid_t getIdPid() const;
    Player(struct game const* dataGame, pid_t id, char _view, unsigned int _number);
    void movePlayer(const struct game *dataGAme, std::mutex * lock);
    void listenPlayer(const bool *flag, std::mutex*lock);
    void addPoints(unsigned int value);
    void setScore(unsigned int score);
    unsigned int getScore() const;

};


#endif //GAME_SERVER_PLAYER_H
