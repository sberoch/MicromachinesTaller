//
// Created by alvaro on 1/11/19.
//

#include "EnterLobbyEvent.h"

void EnterLobbyEvent::send(Protocol &protocol) {
    std::string toSend = j.dump();
    protocol.send(toSend);
}