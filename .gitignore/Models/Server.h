//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_SERVER_H
#define CHECKERSSERVER_SERVER_H

#include "Utilities.h"
#include <stdexcept>
#include <string>
#include "../Other/json.hpp"
#include "../Other/JsonConversions.h"
#include "Logger.h"
#include "Game.h"
#include "../Enums/ActionType.h"
#include "../Parameters/CreateRoomParameter.h"
#include "../Parameters/JoinRoomParameter.h"
#include "../Other/cpplinq.h"
#include "../Parameters/CloseRoomResult.h"
#include "../Parameters/JoinRoomParameter.h"
#include "../Parameters/LeaveRoomParameter.h"
#include "../Parameters/StartGameParameter.h"
#include "../Enums/PlayerType.h"
#include "../Parameters/SurrenderParameter.h"
#include "../Parameters/MakeMoveParameter.h"
#include "../Parameters/UpdateGameboardParameter.h"
#include "../ViewModels/Pawn.h"
#include <algorithm>

using json = nlohmann::json;
using namespace std;
using namespace cpplinq;

void *handleRequest(void *arg);

json receiveRequest(int clientDescriptor);

void sendResponse(int clientDescriptor, string response);

UpdateGameboardParameter getUpdateGameboardParameter(Game game, PlayerType playerType);

vector<Pawn> getPawnsWithoutMoves(vector<Pawn> pawns);

void sendUpdateGameboardMessage(Player player, string json);

vector<Pawn> getPawns(Game game, PlayerType playerType);

json getResult(ActionType actionType, json parameter, int clientDescriptor);

json makeMove(MakeMoveParameter parameter);

json surrender(SurrenderParameter parameter);

json leaveRoom(LeaveRoomParameter parameter);

json joinRoom(JoinRoomParameter parameter, int descriptor);

json closeRoom(CloseRoomParameter parameter);

json startGame(StartGameParameter parameter);

json createRoom(CreateRoomParameter parameter, int hostDescriptor);

void updateGameboard(Game game);

struct client {
    int descriptor;
    struct sockaddr_in address;
};

vector<Game> games = vector<Game>();

class Server {
public:
    void start() {
        pthread_t tid;
        socklen_t slt;
        int serverDescriptor, on = 1;
        struct sockaddr_in serverAddress;

        memset(&serverAddress, 0, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(SERVER_PORT);

        if ((serverDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            ERROR("socket()")
        }

        if (setsockopt(serverDescriptor, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on)) < 0) {
            ERROR("setsockopt()")
        }

        if (bind(serverDescriptor, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
            ERROR("bind()")
        }

        if (listen(serverDescriptor, QUEUE_SIZE) < 0) {
            ERROR("listen()")
        }

        while (true) {
            struct client *client = (struct client *) malloc(sizeof(struct client));
            slt = sizeof(client->address);

            if ((client->descriptor = accept(serverDescriptor, (struct sockaddr *) &client->address, &slt)) < 0) {
                ERROR("accept()")
            }

            if (pthread_create(&tid, NULL, handleRequest, client) < 0) {
                ERROR("pthread_create()")
            }

            pthread_detach(tid);
        }

        close(serverDescriptor);
    }
};

void *handleRequest(void *arg) {
    struct client *client = (struct client *) arg;

    try {
        while (true) {
            json parameterJson = receiveRequest(client->descriptor);

            //log("Action type: " + parameterJson.at("action_type").get<int>());
            //log("Parameter: " + parameterJson.dump());

            json resultJson = getResult((ActionType) parameterJson.at("action_type").get<int>(), parameterJson, client->descriptor);

            //log("Result: " + resultJson.dump());
            //log("");

            sendResponse(client->descriptor, resultJson.dump());

            fflush(stdout);
        }
    }
    catch (exception ex){
          // ignore
    };

    close(client->descriptor);
    free(client);

    return EXIT_SUCCESS;
}

json getResult(ActionType actionType, json parameter, int clientDescriptor) {
    try {
        switch (actionType) {
            case CreateRoom:
                return createRoom(parameter, clientDescriptor);
            case StartGame:
                return startGame(parameter);
            case CloseRoom:
                return closeRoom(parameter);
            case JoinRoom:
                return joinRoom(parameter, clientDescriptor);
            case LeaveRoom:
                return leaveRoom(parameter);
            case Surrender:
                return surrender(parameter);
            case MakeMove:
                return makeMove(parameter);
            case UpdateGameboard:
                return Result::createError("Action can't be executed by client");
            default:
                throw runtime_error("Unknown action type");
        }
    }
    catch (const std::exception &ex) {
        return Result::createError(ex.what());
    }
}

void replaceGame(Game game){
    for(unsigned int i = 0; i < games.size(); i++){
        if(games[i] == game){
            games[i] = game;
            break;
        }
    }
}

json createRoom(CreateRoomParameter parameter, int hostDescriptor) {
    auto x = parameter;

    Game game = Game(hostDescriptor);

    games.push_back(game);

    return CreateRoomResult(game.host.sessionId, game.roomId);
}

json startGame(StartGameParameter parameter) {
    if (!(from(games) >> any([parameter](Game game) { return game.host.sessionId == parameter.sessionId; }))) {
        return Result::createError("Couldn't find active room");
    }

    Game game = from(games) >> where([parameter](Game game) { return game.host.sessionId == parameter.sessionId; })
                            >> first();

    if (game.guest.sessionId == "") {
        return Result::createError("You can't start game without second player");
    }

    game.startGame();
    updateGameboard(game);

    sendResponse(game.guest.descriptor, ((json) parameter).dump());

    replaceGame(game);

    return Result::createSuccess();
}

json closeRoom(CloseRoomParameter parameter) {
    if (!(from(games) >> any([parameter](Game game) { return game.host.sessionId == parameter.sessionId; }))) {
        return Result::createError("Couldn't find active room");
    }

    Game game = from(games) >> where([parameter](Game game) { return game.host.sessionId == parameter.sessionId; })
                            >> first();

    if (game.inProgress()) {
        return Result::createError("Game is in progress");
    }

    games.erase(remove(games.begin(), games.end(), game), games.end());

    return Result::createSuccess();
}

json joinRoom(JoinRoomParameter parameter, int descriptor) {
    if (!(from(games) >> any([parameter](Game game) { return game.roomId == parameter.roomId; }))) {
        return Result::createError("Couldn't find active room");
    }

    Game game = from(games) >> where([parameter](Game game) { return game.roomId == parameter.roomId; }) >> first();

    if (game.guest.sessionId != "") {
        return Result::createError("Room is full");
    }

    game.addGuest(descriptor);
    sendResponse(game.host.descriptor, ((json) parameter).dump());

    replaceGame(game);

    return JoinRoomResult(game.guest.sessionId);
}

json leaveRoom(LeaveRoomParameter parameter) {
    if (!(from(games) >> any([parameter](Game game) { return game.guest.sessionId == parameter.sessionId; }))) {
        return Result::createError("Couldn't find active room");
    }

    Game game = from(games) >> where([parameter](Game game) { return game.guest.sessionId == parameter.sessionId; }) >> first();

    if (game.inProgress()) {
        return Result::createError("Game is in progress");
    }

    sendResponse(game.host.descriptor, ((json) parameter).dump());
    game.removeGuest();

    replaceGame(game);

    return Result::createSuccess();
}

json surrender(SurrenderParameter parameter) {
    if (!(from(games) >> any([parameter](Game game) {
        return game.guest.sessionId == parameter.sessionId || game.host.sessionId == parameter.sessionId;
    }))) {
        return Result::createError("Couldn't find active room");
    }

    Game game = from(games) >> where([parameter](Game game) {
        return game.guest.sessionId == parameter.sessionId || game.host.sessionId == parameter.sessionId;
    }) >> first();

    auto playerType = game.host.sessionId == parameter.sessionId ? Host : Guest;

    game.surrender(playerType);

    updateGameboard(game);

    replaceGame(game);

    return Result::createSuccess();
}

json makeMove(MakeMoveParameter parameter) {
    Game game = from(games) >> where([parameter](Game g) {
        return g.guest.sessionId == parameter.sessionId || g.host.sessionId == parameter.sessionId;
    }) >> first();

    game.makeMove(parameter.moveId);

    updateGameboard(game);

    replaceGame(game);

    return Result::createSuccess();
}

void updateGameboard(Game game) {
    json hostJson = getUpdateGameboardParameter(game, Host);
    json guestJSon = getUpdateGameboardParameter(game, Guest);

    sendUpdateGameboardMessage(game.host, hostJson.dump());
    sendUpdateGameboardMessage(game.guest, guestJSon.dump());
}

UpdateGameboardParameter getUpdateGameboardParameter(Game game, PlayerType playerType)
{
    return UpdateGameboardParameter(game.status, getPawns(game, playerType));
}

void sendUpdateGameboardMessage(Player player, string json)
{
    if (player.descriptor != -1)
    {
        sendResponse(player.descriptor, json);

        //log(json);
    }
}

vector<Pawn> getPawns(Game game, PlayerType playerType)
{
    vector<Pawn> hostPawns = game.getHostPawns();
    vector<Pawn> guestPawns = game.getGuestPawns();

    if (game.status == HostTurn && playerType == Host)
    {
        guestPawns = getPawnsWithoutMoves(guestPawns);
    }
    else if ((game.status == HostTurn && playerType == Guest)
            ||(game.status == GuestTurn && playerType == Host))
    {
        hostPawns = getPawnsWithoutMoves(hostPawns);
        guestPawns = getPawnsWithoutMoves(guestPawns);
    }
    else
    {
        hostPawns = getPawnsWithoutMoves(hostPawns);
    }

    hostPawns.insert(hostPawns.end(), guestPawns.begin(), guestPawns.end());

    return hostPawns;
}

vector<Pawn> getPawnsWithoutMoves(vector<Pawn> pawns){
    vector<Pawn> result = vector<Pawn>();

    for(Pawn pawn: pawns){
        result.push_back(Pawn(pawn.owner, pawn.position, vector<Move>(), pawn.isPromoted));
    }

    return result;
}

json receiveRequest(int clientDescriptor) {
    int received = 0;
    int n = 0;
    char buffer[BUFFER_SIZE] = {};

    string request = "";

    while ((n = read(clientDescriptor, buffer, BUFFER_SIZE)) > 0) {
        if (n < 0) {
            ERROR("read()")
        }

        received += n;

        if (buffer[received-1] == '|') {
            buffer[received-1] = 0;
            request += string(buffer);
            break;
        }

        request += string(buffer);

        memset(buffer, 0, BUFFER_SIZE);
    }

    return json::parse(request);
}

void sendResponse(int clientDescriptor, string response) {
    int n = 0;
    unsigned int sent = 0;

    response += string("|");

    //printf("%d: \n", clientDescriptor);
    //fflush(stdout);

    do {
        string segment = response.substr(sent, sent + BUFFER_SIZE);

        if ((n = write(clientDescriptor, segment.c_str(), segment.length())) < 0) {
            ERROR("write()")
        }

        //printf(segment.c_str());
        //fflush(stdout);

        sent += n;
    } while (sent < response.length());

    //printf("\n\n\n");
}

#endif //CHECKERSSERVER_SERVER_H
