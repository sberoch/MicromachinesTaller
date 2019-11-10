//
// Created by alvaro on 1/11/19.
//

#include "EnterRoomEvent.h"

EnterRoomEvent::EnterRoomEvent(int id, int selectedRoom) {
	j["type"] = ENTER_ROOM;
	j["client_id"] = id;
	j["selected_room"] = selectedRoom;
}

void EnterRoomEvent::send(Protocol &protocol) {
    std::string toSend = j.dump();
    protocol.send(toSend);
}