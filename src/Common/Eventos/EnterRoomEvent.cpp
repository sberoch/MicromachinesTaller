//
// Created by alvaro on 1/11/19.
//

#include "EnterRoomEvent.h"

void EnterRoomEvent::send(Protocol &protocol, int id) {
    j["type"] = ENTER_ROOM;
    j["id"] = id;
    //AGREGAR ATRIBUTOS.
    std::string toSend = j.dump();
    protocol.send(toSend);
}

EnterRoomEvent::~EnterRoomEvent() = default;
