//
// Created by alvaro on 19/11/19.
//

#include <iostream>
#include "EndSnapshot.h"
#include "../Constants.h"

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
    int colour = getColourFromId(idFromRoom);
    j["finished_queue"].push_back(colour);
}

void EndSnapshot::send(Protocol &protocol) {
    std::string message = j.dump();
    std::cout << "Dumped:" << message << std::endl;
    protocol.send(message);
}

int EndSnapshot::getColourFromId(int id) {
    switch(id){
        case 0:
            return TYPE_CAR_RED;
        case 1:
            return TYPE_CAR_BLUE;
        case 2:
            return TYPE_CAR_YELLOW;
        case 3:
            return TYPE_CAR_GREEN;
        default:
            return -1;
    }
}
