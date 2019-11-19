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
	try{
		SnapshotEvent* gameSnap;
		LobbySnapshot* lobbySnap;

		while(!_isGameMode) {
			lobbySnap = new LobbySnapshot(protocol);
			lobbyRecvQueue.push(lobbySnap);

			int id = lobbySnap->getMyId();
			if (lobbySnap->gameStarted(id)) {
				_isGameMode = true;
			}
		}
		while(_isGameMode) {
			gameSnap = new SnapshotEvent(protocol);
			gameRecvQueue.push(gameSnap);
		}

	} catch (std::exception &e) {
		std::cerr << "Error from Receiver Thread" << e.what() << std::endl;
	} catch (...){
        std::cerr << "Unknown error from Receiver Thread" << std::endl;
	}
	_done = true;
}
bool ReceiverThread::finished() const {
	return _done;
}

void ReceiverThread::setGameMode() {
	_isGameMode = true;
}