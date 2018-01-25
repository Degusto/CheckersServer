//
// Created by student on 23.01.18.
//

#ifndef CHECKERSSERVER_GAME_H
#define CHECKERSSERVER_GAME_H

#include <atomic>
#include "../ViewModels/Player.h"
#include "../Enums/PlayerType.h"
#include "../Enums/GameStatus.h"
#include "../ViewModels/Pawn.h"
#include "../Other/cpplinq.h"

using namespace cpplinq;

class Game
{
public:
    string roomId;
    GameStatus status;
    Player guest;
    Player host;
    vector<Pawn> pawns;

    Game& operator =(const Game& game)
    {
        this->roomId = game.roomId;
        this->status = game.status;
        this->guest = game.guest;
        this->host = game.host;
        this->pawns = game.pawns;

        return *this;
    }

    Game(int hostDescriptor)
    {
        roomId = generateUniqueId();
        guest = Player();
        host = Player(generateUniqueId(), hostDescriptor);
    };

    vector<Pawn> getGuestPawns(){
        return from(pawns) >> where([](Pawn pawn){return pawn.owner == Guest;}) >> to_vector();
    }

    vector<Pawn> getHostPawns(){
        return from(pawns) >> where([](Pawn pawn){return pawn.owner == Host;}) >> to_vector();
    }

    bool operator ==(Game game){
        return game.roomId == this->roomId;
    }

    bool inProgress(){
        return status == HostTurn || status == GuestTurn;
    }

    void addGuest(int guestDescriptor) {
        guest = Player(generateUniqueId(), guestDescriptor);
    }

    void removeGuest() {
        guest = Player();
    }

    void startGame() {
        if (inProgress())
        {
            throw runtime_error("Game is already in progress");
        }

        vector<Pawn> hostPawns = generateHostPawns();
        vector<Pawn> guestPawns = generateGuestPawns();

        pawns.clear();
        pawns.insert(pawns.end(), hostPawns.begin(), hostPawns.end());
        pawns.insert(pawns.end(), guestPawns.begin(), guestPawns.end());

        addMoves();

        status = HostTurn;
    }

    void surrender(PlayerType type){
        if (!inProgress())
        {
            throw runtime_error("Game isn't in progress");
        }

        status = type == Host ? GuestWithdrew : HostWithdrew;
    }

    void makeMove(int moveId) {
        if (!inProgress())
        {
            throw runtime_error("Game isn't in progress");
        }

        makeMove(moveId, status == HostTurn ? getHostPawns() : getGuestPawns());
    }

private:
    int rowCount = 8;
    int columnCount = 8;

    string generateUniqueId(){
        static atomic<int> id;

        return to_string(id++);
    }

    vector<Pawn> generateHostPawns()
    {
        vector<Pawn> pawns = vector<Pawn>();

        for (int i = 0; i < 3; i++)
        {
            for (int j = i % 2 == 0 ? 1 : 0; j < columnCount; j += 2)
            {
                pawns.push_back(Pawn(Host, Position(i, j), vector<Move>(), false));
            }
        }

        return pawns;
    }

    vector<Pawn> generateGuestPawns()
    {
        vector<Pawn> pawns = vector<Pawn>();

        for (int i = 5; i < 8; i++)
        {
            for (int j = i % 2 == 0 ? 1 : 0; j < columnCount; j += 2)
            {
                pawns.push_back(Pawn(Guest,Position(i, j), vector<Move>(), false));
            }
        }

        return pawns;
    }

    void makeMove(int moveId, vector<Pawn> playerPawns)
    {
        Pawn pawn = from(playerPawns) >> where([moveId](Pawn p){return (from(p.availableMoves) >> any([moveId](Move m){return m.id == moveId;}));}) >> first();
        Move move = from(pawn.availableMoves) >> where([moveId](Move m){return m.id == moveId;}) >> first();

        if (move.isCapture())
        {
            Pawn pawnToRemove = from(pawns) >> where([move](Pawn p){return p.position.row == move.getMiddlePosition().row && p.position.column == move.getMiddlePosition().column;}) >> first();
            pawns.erase(remove(pawns.begin(), pawns.end(), pawnToRemove), pawns.end());
        }

        pawn.position = move.destinatedPosition;
        pawn.isPromoted = pawn.isPromoted || isInPromotedPosition(pawn);

        for(unsigned int i = 0; i < pawns.size(); i++)
        {
            if(pawns[i] == pawn){
                pawns[i] = pawn;
            }
        }

        addMoves();

        updateGameStatus();
    }

    bool isInPromotedPosition(Pawn pawn)
    {
        int HostKingRowIndex = 7;
        int GuestKingRowIndex = 0;

        return pawn.owner == Host ? pawn.position.row == HostKingRowIndex : pawn.position.row == GuestKingRowIndex;
    }

    void updateGameStatus()
    {
        if (status == HostTurn)
        {
            bool canMakeMove = from(getGuestPawns()) >> any([](Pawn p){return p.availableMoves.size() > 0;});

            status = canMakeMove ? GuestTurn : HostWon;
        }
        else if (status == GuestTurn)
        {
            bool canMakeMove = from(getHostPawns()) >> any([](Pawn p){return p.availableMoves.size() > 0;});

            status = canMakeMove ? HostTurn : GuestWon;
        }

        if (!inProgress())
        {
            for(unsigned int i = 0; i < pawns.size(); i++)
            {
                Pawn& pawn = pawns[i];

                pawn.availableMoves.clear();

                pawns[i] = pawn;
            }
        }
    }

    void addMoves(){
        for(unsigned int i = 0; i < pawns.size(); i++)
        {
            Pawn& pawn = pawns[i];

            pawn.availableMoves.clear();

            auto position = pawn.position;

            Position leftTop = Position(position.row - 1, position.column - 1);
            Position rightTop = Position(position.row - 1, position.column + 1);
            Position leftDown = Position(position.row + 1, position.column - 1);
            Position rightDown = Position(position.row + 1, position.column + 1);

            if (pawn.isPromoted || pawn.owner == Host)
            {
                addMove(leftDown, pawn);
                addMove(rightDown, pawn);
            }

            if (pawn.isPromoted || pawn.owner == Guest)
            {
                addMove(leftTop, pawn);
                addMove(rightTop, pawn);
            }
        }
    }

    void addMove(Position& position, Pawn& pawn, bool lookForCapture = true)
    {
        bool isValidPosition = position.row >= 0 && position.row <= rowCount - 1 && position.column >= 0 && position.column <= columnCount - 1;
        bool isAvailable = !(from(pawns) >> any([position](Pawn p){return p.position.row == position.row && p.position.column == position.column;}));
        bool isOccupiedByEnemy = isValidPosition && !isAvailable && (from(pawns) >> where([position](Pawn p){return p.position.row == position.row && p.position.column == position.column;}) >> first()).owner != pawn.owner;

        if (isValidPosition && isAvailable)
        {
            pawn.availableMoves.push_back(Move(position, pawn.position));
        }
        else if (!isAvailable && isOccupiedByEnemy && lookForCapture)
        {
            position.row += position.row - pawn.position.row;
            position.column += position.column - pawn.position.column;

            addMove(position, pawn, false);
        }
    }
};

#endif //CHECKERSSERVER_GAME_H
