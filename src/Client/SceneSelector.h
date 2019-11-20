#ifndef SCENE_SELECTOR_H
#define SCENE_SELECTOR_H

#include "SdlWindow.h"
#include "SdlTexture.h"
#include "BaseScene.h"
#include "ReceiverThread.h"
#include "SenderThread.h"
#include "../Common/SafeQueue.h"
#include "../Common/Queue.h"
#include "../Common/Event/Event.h"
#include "../Common/Event/SnapshotEvent.h"
#include "../Common/Event/LobbySnapshot.h"
#include "../Common/Event/EndSnapshot.h"
#include "../Common/Protocol.h"
#include "PlayerDescriptor.h"
#include <map>

class SceneSelector {
private:
	SdlWindow window;
	std::map<int, BaseScene*> scenes;
	int currentScene;
	SDL_Event event;
	bool done;
	bool fullscreen;

	Protocol protocol;

	Queue<SnapshotEvent*> gameRecvQueue;
	Queue<LobbySnapshot*> lobbyRecvQueue;
	Queue<EndSnapshot*> endRecvQueue;
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
    int handle(BaseScene* scene);
};

#endif // SCENE_SELECTOR_H