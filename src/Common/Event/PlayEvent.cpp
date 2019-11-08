#include "PlayEvent.h"

PlayEvent::PlayEvent(int id) {
	j["type"] = PLAY;
	j["client_id"] = id;
}

void PlayEvent::send(Protocol &protocol) {
    std::string toSend = j.dump();
    protocol.send(toSend);
}