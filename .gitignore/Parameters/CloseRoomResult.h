//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_CLOSEROOMRESULT_H
#define CHECKERSSERVER_CLOSEROOMRESULT_H

#include "Parameter.h"

class CloseRoomParameter : public Parameter
{
public:
    CloseRoomParameter() : CloseRoomParameter("")
    {

    }
    CloseRoomParameter(string sessionId) : Parameter(sessionId, CloseRoom)
    {
    }
};

#endif //CHECKERSSERVER_CLOSEROOMRESULT_H
