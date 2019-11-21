#ifndef SCENE_SELECTOR_H
#define SCENE_SELECTOR_H

#include "SdlWindow.h"
#include "BaseScene.h"
#include "ReceiverThread.h"
#include "SenderThread.h"
#include "../Common/SafeQueue.h"
#include "../Common/Event/Event.h"
#include "../Common/Event/SnapshotEvent.h"
#include "../Common/Event/LobbySnapshot.h"
#include "../Common/Event/EndSnapshot.h"
#include "../Common/Protocol.h"
#include "PlayerDescriptor.h"
#include "../Common/Constants.h"
#include <map>

typedef std::shared_ptr<BaseScene> ScenePtr;

class SceneSelector {
private:
	SdlWindow window;
	std::map<int, ScenePtr> scenes;
	Scene currentScene;

	Protocol protocol;

	SafeQueue<std::shared_ptr<SnapshotEvent>> gameRecvQueue;
	SafeQueue<std::shared_ptr<LobbySnapshot>> lobbyRecvQueue;
	SafeQueue<std::shared_ptr<EndSnapshot>> endRecvQueue;
	SafeQueue<std::shared_ptr<Event>> sendQueue;

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