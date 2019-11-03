//
// Created by alvaro on 1/11/19.
//

#include "PlayAsBotEvent.h"

void PlayAsBotEvent::send(Protocol &protocol) {
    std::string toSend = j.dump();
    protocol.send(toSend);
}
