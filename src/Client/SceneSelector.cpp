#include "SceneSelector.h"
#include "../Common/Constants.h"
#include "GameScene.h"

#define MAX_COMMANDS_ENQUEUED 100

SceneSelector::SceneSelector(int xScreen, int yScreen,
		const std::string& host, const std::string& port) : 
	window(xScreen, yScreen),
	protocol(host, port),
	sendQueue(MAX_COMMANDS_ENQUEUED),
	receiver(recvQueue, protocol),
	sender(sendQueue, protocol),
	currentScene(SCENE_GAME) /*TODO: SCENE_MENU*/ {
		//scenes.insert(std::make_pair(SCENE_MENU, new MenuScene(window)));
		//scenes.insert(std::make_pair(SCENE_LOBBY, new LobbyScene(window)));
		scenes.insert(std::make_pair(SCENE_GAME, new GameScene(window, recvQueue, sendQueue)));
		
		receiver.start();
		sender.start();
	}

void SceneSelector::run() {
	BaseScene* scene;
	bool done = false;
	while(!done) {
	    scene = scenes.at(currentScene);
	    scene->update();
	    scene->draw();
	    currentScene = scene->handle();
	    if (scene->done()) {
	    	done = true;
	    	protocol.forceShutDown(); //No estoy seguro de que vaya aca
	    }
	}
}

SceneSelector::~SceneSelector() {
	receiver.join();
	sender.join();

	for (auto& it : scenes) {
		delete it.second;
	}
}