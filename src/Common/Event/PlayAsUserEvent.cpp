//
// Created by alvaro on 1/11/19.
//

#include "PlayAsUserEvent.h"

void PlayAsUserEvent::send(Protocol &protocol) {
    std::string toSend = j.dump();
    protocol.send(toSend);
}