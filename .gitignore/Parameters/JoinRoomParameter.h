//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_JOINROOMRPARAMETER_H
#define CHECKERSSERVER_JOINROOMRPARAMETER_H

#include "Parameter.h"

class JoinRoomParameter : public Parameter
{
public:
    string roomId;

    JoinRoomParameter() : JoinRoomParameter("")
    {
    }

    JoinRoomParameter(string roomId) : Parameter("", JoinRoom)
    {
        this->roomId = roomId;
    }
};

#endif //CHECKERSSERVER_JOINROOMRPARAMETER_H
