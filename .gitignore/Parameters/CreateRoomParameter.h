//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_CREATEROOMPARAMETER_H
#define CHECKERSSERVER_CREATEROOMPARAMETER_H

#include "Parameter.h"

class CreateRoomParameter : public Parameter
{
public:
    CreateRoomParameter() : Parameter("", CreateRoom)
    {
    }
};

#endif //CHECKERSSERVER_CREATEROOMPARAMETER_H
