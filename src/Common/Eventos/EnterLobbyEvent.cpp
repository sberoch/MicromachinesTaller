//
// Created by alvaro on 1/11/19.
//

#include "EnterLobbyEvent.h"

void EnterLobbyEvent::send(Protocol &protocol, int id) {
    j["type"] = ENTER_LOBBY;
    j["id"] = id;
    //AGREGAR ATRIBUTOS
    std::string toSend = j.dump();
    protocol.send(toSend);
}

EnterLobbyEvent::~EnterLobbyEvent() = default;
