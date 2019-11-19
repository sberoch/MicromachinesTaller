#ifndef SCENE_SELECTOR_H
#define SCENE_SELECTOR_H

#include "SdlWindow.h"
#include "BaseScene.h"
#include "ReceiverThread.h"
#include "SenderThread.h"
#include "../Common/SafeQueue.h"
#include "../Common/Queue.h"
#include "../Common/Event/Event.h"
#include "../Common/Event/SnapshotEvent.h"
#include "../Common/Event/LobbySnapshot.h"
#include "../Common/Protocol.h"
#include "PlayerDescriptor.h"
#include <map>

class SceneSelector {
private:
	SdlWindow window;
	std::map<int, BaseScene*> scenes;
	int currentScene;

	Protocol protocol;

	Queue<SnapshotEvent*> gameRecvQueue;
	Queue<LobbySnapshot*> lobbyRecvQueue;
	SafeQueue<Event*> sendQueue;

	ReceiverThread receiver;
	SenderThread sender;
	
	PlayerDescriptor player;

public:
	SceneSelector(int xScreen, int yScreen,
		const std::string& host, const std::string& port);
	void run();
	~SceneSelector();

private:
	void sleep(int milliseconds);
};

#endif // SCENE_SELECTOR_H