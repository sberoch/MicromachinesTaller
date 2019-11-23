//
// Created by alvaro on 1/11/19.
//

#include "CommandEvent.h"
#include "EventCreator.h"
#include "SnapshotEvent.h"
#include "EnterLobbyEvent.h"
#include "EnterRoomEvent.h"
#include "PlayEvent.h"
#include "CreateRoomEvent.h"
#include "LobbySnapshot.h"
#include "GoBackToMenuEvent.h"
#include <memory>
#include <iostream>

//TODO:Faltan crear los eventos.
std::shared_ptr<Event> EventCreator::makeEvent(const std::string& recvdEvent){
    auto j = json::parse(recvdEvent);
    int type = j["type"].get<int>();
    int id;
    int selectedRoom, selectedPlayer;
    std::cout << "Type: " << type << std::endl;

    switch (type) {
        case COMMAND:
            return std::shared_ptr<Event>(new CommandEvent(j));
        case GAME_SNAPSHOT:
            return std::shared_ptr<Event>(new SnapshotEvent);
        case ENTER_LOBBY:
            return std::shared_ptr<Event>(new EnterLobbyEvent);
        case ENTER_ROOM:
            id = j["client_id"].get<int>();
            selectedRoom = j["selected_room"].get<int>();
            selectedPlayer = j["selected_player"].get<int>();
            return std::shared_ptr<Event>(new EnterRoomEvent(id, selectedRoom, selectedPlayer));
        case CREATE_ROOM:
            return std::shared_ptr<Event>(new CreateRoomEvent);
        case PLAY:
            id = j["client_id"].get<int>();
            return std::shared_ptr<Event>(new PlayEvent(id));
        case MENU:
            id = j["client_id"].get<int>();
            return std::shared_ptr<Event>(new GoBackToMenuEvent(id));

        default:
            throw std::runtime_error("Wrong event type");
    }


//    if (type == COMMAND)
//        return std::shared_ptr<Event>(new CommandEvent(j));
//    else if (type == SNAPSHOT)
//        return std::shared_ptr<Event>(new SnapshotEvent);
//    else if (type == ENTER_LOBBY) {
//        return std::shared_ptr<Event>(new EnterLobbyEvent);
//    }
//    else if (type == PLAY_AS_USER){
//        int clientId = j["client_id"].get<int>();
//        return std::shared_ptr<Event>(new PlayAsUserEvent(clientId));
//    } else if (type == PLAY_AS_BOT){
//        int clientId = j["client_id"].get<int>();
//        return std::shared_ptr<Event>(new PlayAsBotEvent(clientId));
//    } else if (type == ENTER_ROOM)
//        return std::shared_ptr<Event>(new EnterRoomEvent(clientId));
//    else if (type == PLAY)
//        return std::shared_ptr<Event>(new PlayEvent(clientId));
//    else
//        throw std::runtime_error("Wrong event type");
}