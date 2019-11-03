//
// Created by alvaro on 1/11/19.
//

#include "CommandEvent.h"

CommandEvent::CommandEvent(json j) {
	this->j = std::move(j);
}

CommandEvent::CommandEvent(InputEnum cmd_id) {
	j["type"] = COMMAND;
    j["cmd_id"] = cmd_id;
}

void CommandEvent::send(Protocol &protocol) {
    std::string toSend = j.dump();
    protocol.send(toSend);
}