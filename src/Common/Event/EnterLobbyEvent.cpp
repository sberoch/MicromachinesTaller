//
// Created by alvaro on 1/11/19.
//

#include "EnterLobbyEvent.h"

EnterLobbyEvent::EnterLobbyEvent() {
	j["type"] = ENTER_LOBBY;
}

void EnterLobbyEvent::send(Protocol &protocol) {
    std::string toSend = j.dump();
    protocol.send(toSend);
}