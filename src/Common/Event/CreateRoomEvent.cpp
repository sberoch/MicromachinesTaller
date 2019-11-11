#include "CreateRoomEvent.h"

CreateRoomEvent::CreateRoomEvent() {
	j["type"] = CREATE_ROOM;
}

void CreateRoomEvent::send(Protocol &protocol) {
    std::string toSend = j.dump();
    protocol.send(toSend);
}