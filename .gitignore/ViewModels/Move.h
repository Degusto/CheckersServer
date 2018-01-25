//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_MOVE_H
#define CHECKERSSERVER_MOVE_H

#include "Position.h"
#include <string>
#include <stdexcept>
#include <atomic>

using namespace std;

class Move
{
public:
    int id;
    Position destinatedPosition;
    Position sourcePosition;

    Move() : Move(Position(), Position()){

    }

    Move(Position destinatedPosition, Position sourcePosition){
        static atomic<int> lastId;

        id = lastId++;
        this->destinatedPosition = destinatedPosition;
        this->sourcePosition = sourcePosition;
    }

    Move& operator=(const Move& move)
    {
        this->id = move.id;
        this->destinatedPosition = move.destinatedPosition;
        this->sourcePosition = move.sourcePosition;

        return *this;
    }

    Position getMiddlePosition() const
    {
        if(!isCapture())
        {
            throw runtime_error("Move doesn't capture");
        }

        int row = sourcePosition.row - (sourcePosition.row - destinatedPosition.row) / 2;
        int column = sourcePosition.column - (sourcePosition.column - destinatedPosition.column) / 2;

        return Position(row, column);
    }

    bool isCapture() const
    {
        return abs(sourcePosition.row - destinatedPosition.row) > 1 || abs(sourcePosition.column - destinatedPosition.column) > 1;
    }
};

#endif //CHECKERSSERVER_MOVE_H
