//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_PAWN_H
#define CHECKERSSERVER_PAWN_H

#include <vector>
#include "Position.h"
#include "Move.h"
#include "../Enums/PlayerType.h"

static atomic<int> idSeed;

class Pawn
{
public:
    bool isPromoted;
    PlayerType owner;
    Position position = Position(0,0);
    vector<Move> availableMoves = vector<Move>();

    Pawn() {
        id = idSeed++;
    }

    bool operator ==(Pawn pawn){
        return this->id == pawn.id;
    }

    Pawn(PlayerType owner, Position position, vector<Move> availableMoves, bool isPromoted) : Pawn() {
        this->owner = owner;
        this->position = position;
        this->isPromoted = isPromoted;
        this->availableMoves = availableMoves;
    }

    Pawn& operator =(const Pawn& pawn)
    {
        this->isPromoted = pawn.isPromoted;
        this->owner = pawn.owner;
        this->position = pawn.position;
        this->availableMoves = pawn.availableMoves;
        this->id = pawn.id;

        return *this;
    }
private:
    int id;
};

#endif //CHECKERSSERVER_PAWN_H
