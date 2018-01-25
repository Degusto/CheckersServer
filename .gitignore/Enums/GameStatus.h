//
// Created by student on 12.01.18.
//

#ifndef CHECKERSSERVER_GAMESTATUS_H
#define CHECKERSSERVER_GAMESTATUS_H

enum GameStatus
{
    None = 0,
    HostTurn = 1,
    GuestTurn = 2,
    HostWon = 3,
    GuestWon = 4,
    HostWithdrew = 5,
    GuestWithdrew = 6
};

#endif //CHECKERSSERVER_GAMESTATUS_H
