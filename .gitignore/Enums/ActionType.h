//
// Created by student on 12.01.18.
//

#ifndef CHECKERSSERVER_ACTIONTYPE_H
#define CHECKERSSERVER_ACTIONTYPE_H

enum ActionType
{
    Unknown = 0,
    CreateRoom = 1,
    CloseRoom = 2,
    JoinRoom = 3,
    LeaveRoom = 4,
    StartGame = 5,
    Surrender = 6,
    MakeMove = 7,
    UpdateGameboard = 8
};

#endif //CHECKERSSERVER_ACTIONTYPE_H
