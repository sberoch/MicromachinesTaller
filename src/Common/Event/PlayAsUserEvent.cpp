//
// Created by alvaro on 1/11/19.
//

#include "PlayAsUserEvent.h"

PlayAsUserEvent::PlayAsUserEvent(int id) {
	j["type"] = PLAY_AS_USER;
	j["client_id"] = id;
}

void PlayAsUserEvent::send(Protocol &protocol) {
    std::string toSend = j.dump();
    protocol.send(toSend);
}