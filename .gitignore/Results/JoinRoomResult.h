//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_JOINROOMRESULT_H
#define CHECKERSSERVER_JOINROOMRESULT_H

#include "Result.h"

class JoinRoomResult
{
public:
    string sessionId;

    JoinRoomResult(string sessionId){
        this->sessionId = sessionId;
    }
};

#endif //CHECKERSSERVER_JOINROOMRESULT_H
