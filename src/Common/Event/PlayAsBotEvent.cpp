//
// Created by alvaro on 1/11/19.
//

#include "PlayAsBotEvent.h"

PlayAsBotEvent::PlayAsBotEvent(int id) {
	j["type"] = PLAY_AS_BOT;
	j["client_id"] = id;
}
void PlayAsBotEvent::send(Protocol &protocol) {
    std::string toSend = j.dump();
    protocol.send(toSend);
}
