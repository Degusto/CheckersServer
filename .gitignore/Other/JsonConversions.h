//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_JSONCONVERSION_H
#define CHECKERSSERVER_JSONCONVERSION_H

#include <string>
#include "../Other/json.hpp"
#include "../Results/Result.h"
#include "../Results/JoinRoomResult.h"
#include "../Results/CreateRoomResult.h"
#include "../Parameters/CloseRoomResult.h"
#include "../Parameters/CreateRoomParameter.h"
#include "../Parameters/JoinRoomParameter.h"
#include "../Parameters/LeaveRoomParameter.h"
#include "../Parameters/StartGameParameter.h"
#include "../Parameters/SurrenderParameter.h"
#include "../Parameters/MakeMoveParameter.h"
#include "../Parameters/UpdateGameboardParameter.h"

using json = nlohmann::json;

void from_json(const json &j, CloseRoomParameter &result) {
    result.sessionId = j.at("session_id");
    result.actionType = j.at("action_type");
}

void from_json(const json &j, CreateRoomParameter &result) {
    result.sessionId = j.at("session_id");
    result.actionType = j.at("action_type");
}

void to_json(json &j, const JoinRoomParameter &result) {
    j = json
            {
                    {"action_type", (int) result.actionType},
                    {"room_id",     result.roomId},
                    {"session_id",  result.sessionId}
            };
}

void from_json(const json &j, JoinRoomParameter &result) {
    result.roomId = j.at("room_id");
    result.actionType = j.at("action_type");
    result.sessionId = j.at("session_id");
}

void to_json(json &j, const MakeMoveParameter &result) {
    j = json
            {
                    {"action_type", (int) result.actionType},
                    {"move_id",     result.moveId},
                    {"session_id",  result.sessionId}
            };
}

void from_json(const json &j, MakeMoveParameter &result) {
    result.moveId = j.at("move_id");
    result.actionType = j.at("action_type");
    result.sessionId = j.at("session_id");
}

void to_json(json &j, const UpdateGameboardParameter &result) {
    j = json
            {
                    {"action_type", (int) result.actionType},
                    {"game_status",     result.gameStatus},
                    {"session_id",  result.sessionId},
                    {"pawns", result.pawns}
            };
}

void from_json(const json &j, UpdateGameboardParameter &result) {
    result.gameStatus = j.at("game_status");
    result.actionType = j.at("action_type");
    result.sessionId = j.at("session_id");
    result.pawns = j.at("pawns").get<vector<Pawn>>();
}

void to_json(json &j, const Pawn &result) {
    j = json
            {
                    {"is_promoted", (int) result.isPromoted},
                    {"position",  result.position},
                    {"owner",  result.owner},
                    {"available_moves",  result.availableMoves}
            };
}

void from_json(const json &j, Pawn &result) {
    result.isPromoted = j.at("is_promoted");
    result.position = j.at("position");
    result.owner = j.at("owner");
    result.availableMoves = j.at("available_moves").get<vector<Move>>();
}

void to_json(json &j, const Move &result) {
    j = json
            {
                    {"id", result.id},
                    {"destinated_position",  result.destinatedPosition}
            };
}

void from_json(const json &j, Move &result) {
    result.destinatedPosition = j.at("destinated_position");
    result.id = j.at("id");
}

void to_json(json &j, const Position &result) {
    j = json
            {
                    {"row", result.row},
                    {"column",  result.column}
            };
}

void from_json(const json &j, Position &result) {
    result.row = j.at("row");
    result.column = j.at("column");
}

void to_json(json &j, const StartGameParameter &result) {
    j = json
            {
                    {"action_type", (int) result.actionType},
                    {"session_id",  result.sessionId}
            };
}

void from_json(const json &j, StartGameParameter &result) {
    result.sessionId = j.at("session_id");
    result.actionType = j.at("action_type");
}

void to_json(json &j, const LeaveRoomParameter &result) {
    j = json
            {
                    {"action_type", (int) result.actionType},
                    {"session_id",  result.sessionId}
            };
}

void from_json(const json &j, LeaveRoomParameter &result) {
    result.sessionId = j.at("session_id");
    result.actionType = j.at("action_type");
}

void to_json(json &j, const SurrenderParameter &result) {
    j = json
            {
                    {"action_type", (int) result.actionType},
                    {"session_id",  result.sessionId}
            };
}

void from_json(const json &j, SurrenderParameter &result) {
    result.sessionId = j.at("session_id");
    result.actionType = j.at("action_type");
}

void to_json(json &j, const CreateRoomResult &result) {
    j = json
            {
                    {"error",      ""},
                    {"status",     "OK"},
                    {"room_id",    result.roomId},
                    {"session_id", result.sessionId}
            };
}

void to_json(json &j, const JoinRoomResult &result) {
    j = json
            {
                    {"error",      ""},
                    {"status",     "OK"},
                    {"session_id", result.sessionId}
            };
}

void to_json(json &j, const Result &result) {
    j = json
            {
                    {"error",  result.error},
                    {"status", result.status}
            };
}

#endif //CHECKERSSERVER_JSONCONVERSION_H
