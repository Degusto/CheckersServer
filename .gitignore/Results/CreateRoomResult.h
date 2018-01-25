//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_CREATEROOMRESULT_H
#define CHECKERSSERVER_CREATEROOMRESULT_H

#include "Result.h"

class CreateRoomResult
{
public:
    string roomId = "";
    string sessionId = "";

    CreateRoomResult(string sessionId, string roomId){
        this->sessionId = sessionId;
        this->roomId = roomId;
    }

};

#endif //CHECKERSSERVER_CREATEROOMRESULT_H
