#ifndef SCENE_SELECTOR_H
#define SCENE_SELECTOR_H

#include "SdlWindow.h"
#include "BaseScene.h"
#include "ReceiverThread.h"
#include "../Common/Queue.h"
#include <map>

class SceneSelector {
private:
	SdlWindow window;
	std::map<int, BaseScene*> scenes;
	Queue<ServerSnapshot*> recvQueue;
	//Queue (blocking?) sendQueue;
	ReceiverThread receiver;
	//SenderThread sender;
	int currentScene;


public:
	SceneSelector(int xScreen, int yScreen);
	void run();
	~SceneSelector();
};

#endif // SCENE_SELECTOR_H