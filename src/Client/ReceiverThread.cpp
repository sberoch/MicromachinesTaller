#include "ReceiverThread.h"
#include <iostream>

ReceiverThread::ReceiverThread(Queue<SnapshotEvent*>& gameRecvQueue,
				   			   Queue<LobbySnapshot*>& lobbyRecvQueue, 
				   			   Protocol& protocol) :
	gameRecvQueue(gameRecvQueue),
	lobbyRecvQueue(lobbyRecvQueue),
	protocol(protocol),
	_done(false),
	_isGameMode(false) {}

void ReceiverThread::run() {
	SnapshotEvent* gameSnap;
	LobbySnapshot* lobbySnap;
	while(!_done && !_isGameMode) {
		lobbySnap = new LobbySnapshot(protocol);
		lobbyRecvQueue.push(lobbySnap);
	}
	while(!_done && _isGameMode) {
		gameSnap = new SnapshotEvent(protocol);
		gameRecvQueue.push(gameSnap);
	}
}

void ReceiverThread::kill() {
	_done = true;
}

void ReceiverThread::setGameMode() {
	_isGameMode = true;
}

ReceiverThread::~ReceiverThread() {
	std::cout << "Recv thread killed.\n";
}