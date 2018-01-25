//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_PARAMETER_H
#define CHECKERSSERVER_PARAMETER_H

#include <string>
#include "../Enums/ActionType.h"

using namespace std;

class Parameter
{
public:
    string sessionId = "";
    ActionType actionType = Unknown;

protected:
    Parameter(string sessionId, ActionType actionType)
    {
        this->sessionId = sessionId;
        this->actionType = actionType;
    }
};

#endif //CHECKERSSERVER_PARAMETER_H
