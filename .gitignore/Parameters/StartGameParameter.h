//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_STARTGAMEPARAMETER_H
#define CHECKERSSERVER_STARTGAMEPARAMETER_H

#include "Parameter.h"

class StartGameParameter : public Parameter
{
public:
    StartGameParameter() : StartGameParameter("")
    {

    }

    StartGameParameter(string sessionId) : Parameter(sessionId, StartGame)
    {
    }
};

#endif //CHECKERSSERVER_STARTGAMEPARAMETER_H
