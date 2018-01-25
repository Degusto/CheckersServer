//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_MAKEMOVEPARAMETER_H
#define CHECKERSSERVER_MAKEMOVEPARAMETER_H

#include "Parameter.h"

class MakeMoveParameter : public Parameter
{
public:
    int moveId;

    MakeMoveParameter() : MakeMoveParameter("", -1)
    {

    }

    MakeMoveParameter(string sessionId, int moveId) : Parameter(sessionId, MakeMove)
    {
        this->moveId = moveId;
    }
};

#endif //CHECKERSSERVER_MAKEMOVEPARAMETER_H
