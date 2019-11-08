#include "ReceiverThread.h"
#include <iostream>

ReceiverThread::ReceiverThread(Queue<SnapshotEvent*>& gameRecvQueue,
				   			   Queue<LobbySnapshot*>& lobbyRecvQueue, 
				   			   Protocol& protocol) :
	gameRecvQueue(gameRecvQueue),
	lobbyRecvQueue(lobbyRecvQueue),
	protocol(protocol),
	_done(false),
	_isLobbyMode(false) {}

void ReceiverThread::run() {
	SnapshotEvent* gameSnap;
	LobbySnapshot* lobbySnap;
	while(!_done && _isLobbyMode) {
		lobbySnap = new LobbySnapshot(protocol);
		lobbyRecvQueue.push(lobbySnap);
	}
	while(!_done && !_isLobbyMode) {
		gameSnap = new SnapshotEvent(protocol);
		gameRecvQueue.push(gameSnap);
	}
}

void ReceiverThread::kill() {
	_done = true;
}

void ReceiverThread::setGameMode() {
	_isLobbyMode = true;
}

ReceiverThread::~ReceiverThread() {
	std::cout << "Recv thread killed.\n";
}