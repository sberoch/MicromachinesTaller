#include "ReceiverThread.h"
#include "../Common/Constants.h"
#include <iostream>

ReceiverThread::ReceiverThread(SafeQueue<std::shared_ptr<SnapshotEvent>>& gameRecvQueue,
							   SafeQueue<std::shared_ptr<LobbySnapshot>>& lobbyRecvQueue,
							   SafeQueue<std::shared_ptr<EndSnapshot>>& endRecvQueue,
							   Protocol& protocol, Scene& currentScene) :
	gameRecvQueue(gameRecvQueue),
	lobbyRecvQueue(lobbyRecvQueue),
	endRecvQueue(endRecvQueue),
	protocol(protocol),
	_done(false),
	_isGameMode(false),
	_currentScene(currentScene) {}

void ReceiverThread::run() {
	try {
		while(true) {
		    switch (_currentScene) {
		    	case SCENE_MENU: case SCENE_LOBBY: {
		    		receiveLobbySnapshots();
		    		break;
		    	}
		    	case SCENE_GAME: {
		    		receiveGameSnapshots();
		    		break;
		    	}
		    	case SCENE_END: {
		    		receiveEndSnapshots();
		    		break;
		    	}
		    }
		}
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	} catch (...){
        std::cerr << "Unknown error from Receiver Thread" << std::endl;
	}
	_done = true;
}

void ReceiverThread::receiveLobbySnapshots() {
	std::shared_ptr<LobbySnapshot> lobbySnap(new LobbySnapshot(protocol));
	lobbyRecvQueue.push(lobbySnap);

	int id = lobbySnap->getMyId();
	if (lobbySnap->gameStarted(id)) {
		_currentScene = SCENE_GAME;
	}
}

void ReceiverThread::receiveGameSnapshots() {
	std::shared_ptr<SnapshotEvent> gameSnap(new SnapshotEvent(protocol));
	gameRecvQueue.push(gameSnap);
}

void ReceiverThread::receiveEndSnapshots() {
	std::shared_ptr<EndSnapshot> endSnap(new EndSnapshot(protocol));
	endRecvQueue.push(endSnap);
}

bool ReceiverThread::finished() const {
	return _done;
}