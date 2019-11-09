#include "SceneSelector.h"
#include "../Common/Constants.h"
#include "../Common/SocketError.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "LobbyScene.h"
#include "EndScene.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

SceneSelector::SceneSelector(int xScreen, int yScreen,
		const std::string& host, const std::string& port) : 
	window(xScreen, yScreen),
	protocol(host, port),
	sendQueue(true),
	receiver(gameRecvQueue, lobbyRecvQueue, protocol),
	sender(sendQueue, protocol),
	currentScene(SCENE_MENU) {
		scenes.insert(std::make_pair(SCENE_MENU, new MenuScene(window, sendQueue)));
		scenes.insert(std::make_pair(SCENE_LOBBY, new LobbyScene(window, lobbyRecvQueue, sendQueue)));
		scenes.insert(std::make_pair(SCENE_GAME, new GameScene(window, gameRecvQueue, sendQueue)));
		scenes.insert(std::make_pair(SCENE_END, new EndScene(window)));
		
		receiver.start();
		sender.start();
	}

void SceneSelector::run() {
	BaseScene* scene;
	bool done = false;
	try {
		while(!done) {
			std::clock_t begin = clock();

		    scene = scenes.at(currentScene);
		    scene->update();
		    scene->draw();
		    currentScene = scene->handle();
		    if (scene->done()) {
		    	done = true;
		    	protocol.forceShutDown(); //No estoy seguro de que vaya aca
		    }

		    if (currentScene == SCENE_GAME) {
		    	receiver.setGameMode();
		    }

		    //Check exec time and sleep
		    std::clock_t end = clock();
		    double execTime = double(end - begin) / (CLOCKS_PER_SEC/1000);
		    if (execTime < 25) this->sleep(25 - execTime);
	    }
	} catch (SocketError& se) {
		done = true;
	}
}

void SceneSelector::sleep(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

SceneSelector::~SceneSelector() {
	receiver.kill();

	receiver.join();
	sender.join();

	for (auto& it : scenes) {
		delete it.second;
	}
}