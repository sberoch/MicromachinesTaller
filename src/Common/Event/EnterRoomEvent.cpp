//
// Created by alvaro on 1/11/19.
//

#include "EnterRoomEvent.h"

EnterRoomEvent::EnterRoomEvent(int id) {
	j["type"] = ENTER_ROOM;
	j["client_id"] = id;
}

void EnterRoomEvent::send(Protocol &protocol) {
    std::string toSend = j.dump();
    protocol.send(toSend);
}