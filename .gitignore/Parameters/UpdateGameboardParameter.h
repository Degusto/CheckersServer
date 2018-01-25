//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_UPDATEGAMEBOARDPARAMETER_H
#define CHECKERSSERVER_UPDATEGAMEBOARDPARAMETER_H

#include "../Enums/GameStatus.h"
#include "Parameter.h"
#include "../ViewModels/Pawn.h"

class UpdateGameboardParameter : public Parameter
{
public:
    vector<Pawn> pawns;
    GameStatus gameStatus;

    UpdateGameboardParameter(GameStatus gameStatus, vector<Pawn> pawns) : Parameter("", UpdateGameboard)
    {
        this->pawns = pawns;
        this->gameStatus = gameStatus;
    }
};

#endif //CHECKERSSERVER_UPDATEGAMEBOARDPARAMETER_H
