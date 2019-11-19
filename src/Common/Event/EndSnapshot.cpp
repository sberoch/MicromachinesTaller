//
// Created by alvaro on 19/11/19.
//

#include <iostream>
#include "EndSnapshot.h"

EndSnapshot::EndSnapshot(EndSnapshot &other) {
    this->j = other.j;
}

EndSnapshot::EndSnapshot(Protocol& protocol) {
	std::string serialized = protocol.receive();
    this->j = json::parse(serialized);

    for (auto& finishedPlayer : j["finished_queue"]) {
    	finishedQueue.push_back(finishedPlayer);
    }
}

const std::vector<int>& EndSnapshot::getFinishedQueue() {
	return finishedQueue;
}

void EndSnapshot::addPlayerFinished(int idFromRoom){
    j["finished_queue"].push_back(idFromRoom);
}

void EndSnapshot::send(Protocol &protocol) {
    std::string finishedQueue = j.dump();
    std::cout << "Dumped:" << finishedQueue << std::endl;
    protocol.send(finishedQueue);
}
