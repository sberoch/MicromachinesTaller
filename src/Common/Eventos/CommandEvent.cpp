//
// Created by alvaro on 1/11/19.
//

#include "CommandEvent.h"


void CommandEvent::send(Protocol &protocol, int id) {
    j["type"] = COMMAND;
    j["id"] = id;
    std::string toSend = j.dump();
    protocol.send(toSend);
}

CommandEvent::~CommandEvent() = default;
