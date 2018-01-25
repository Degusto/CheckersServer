//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_SURRENDERPARAMETER_H
#define CHECKERSSERVER_SURRENDERPARAMETER_H

#include "Parameter.h"

class SurrenderParameter : public Parameter
{
public:
    SurrenderParameter() : SurrenderParameter("")
    {

    }
    SurrenderParameter(string sessionId) : Parameter(sessionId, Surrender)
    {
    }
};

#endif //CHECKERSSERVER_SURRENDERPARAMETER_H
