//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_PLAYER_H
#define CHECKERSSERVER_PLAYER_H

#include <string>

using namespace std;

class Player
{
public:
    string sessionId;
    int descriptor;

    Player() : Player("", -1)
    {

    }

    Player(string sessionId, int descriptor)
    {
        this->descriptor = descriptor;
        this->sessionId = sessionId;
    }

    Player& operator =(const Player& player)
    {
        this->sessionId = player.sessionId;
        this->descriptor = player.descriptor;

        return *this;
    }
};

#endif //CHECKERSSERVER_PLAYER_H
