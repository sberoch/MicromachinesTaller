//
// Created by alvaro on 1/11/19.
//

#include "EnterRoomEvent.h"

void EnterRoomEvent::send(Protocol &protocol) {
    std::string toSend = j.dump();
    protocol.send(toSend);
}