cmake_minimum_required(VERSION 3.9)
project(CheckersServer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(CheckersServer main.cpp Enums/PlayerType.h Enums/GameStatus.h Enums/ActionType.h Other/json.hpp Other/cpplinq.h ViewModels/Position.h ViewModels/Move.h ViewModels/Pawn.h Results/Result.h Results/CreateRoomResult.h Results/JoinRoomResult.h Other/JsonConversions.h Parameters/Parameter.h Parameters/CloseRoomResult.h Parameters/CreateRoomParameter.h Parameters/JoinRoomParameter.h Parameters/LeaveRoomParameter.h Parameters/MakeMoveParameter.h Parameters/StartGameParameter.h Parameters/SurrenderParameter.h Parameters/UpdateGameboardParameter.h Models/Logger.h ViewModels/Player.h Models/Server.h Models/CommunicationService.h Models/Utilities.h Models/Game.h)