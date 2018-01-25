//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_POSITION_H
#define CHECKERSSERVER_POSITION_H

class Position
{
public:
    int row;
    int column;

    Position() : Position(-1, -1)
    {
    }

    Position(int row, int column)
    {
        this->row = row;
        this->column = column;
    }

    Position& operator=(const Position& position)
    {
        this->row = position.row;
        this->column = position.column;

        return *this;
    }
};

#endif //CHECKERSSERVER_POSITION_H
