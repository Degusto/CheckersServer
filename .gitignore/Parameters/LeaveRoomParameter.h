//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_LEAVEROOMPARAMETER_H
#define CHECKERSSERVER_LEAVEROOMPARAMETER_H

#include "Parameter.h"

class LeaveRoomParameter : public Parameter
{
public:
    LeaveRoomParameter() : LeaveRoomParameter("")
    {

    }

    LeaveRoomParameter(string sessionId) : Parameter(sessionId, LeaveRoom)
    {
    }
};

#endif //CHECKERSSERVER_LEAVEROOMPARAMETER_H
