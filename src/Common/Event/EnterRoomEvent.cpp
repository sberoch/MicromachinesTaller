//
// Created by alvaro on 1/11/19.
//

#include "EnterRoomEvent.h"

EnterRoomEvent::EnterRoomEvent(int id, int selectedRoom, int selectedPlayer) {
    j["type"] = ENTER_ROOM;
    j["client_id"] = id;
    j["selected_room"] = selectedRoom;
    j["selected_player"] = selectedPlayer;
}

void EnterRoomEvent::send(Protocol &protocol) {
    std::string toSend = j.dump();
    protocol.send(toSend);
}