//
// Created by alvaro on 1/11/19.
//

#include "CommandEvent.h"

CommandEvent::CommandEvent() {}

void CommandEvent::sendEvent(Protocol &protocol, int id) {
    j["id"] = id;
    std::string toSend = j.dump();
    protocol.send(toSend);
}

CommandEvent::~CommandEvent() {}
