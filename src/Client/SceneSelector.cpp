#include "SceneSelector.h"
#include "../Common/Constants.h"
#include "GameScene.h"
#include "MenuScene.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

#define MAX_COMMANDS_ENQUEUED 100

SceneSelector::SceneSelector(int xScreen, int yScreen,
		const std::string& host, const std::string& port) : 
	window(xScreen, yScreen),
	protocol(host, port),
	sendQueue(MAX_COMMANDS_ENQUEUED),
	receiver(recvQueue, protocol),
	sender(sendQueue, protocol),
	currentScene(SCENE_MENU) {
		scenes.insert(std::make_pair(SCENE_MENU, new MenuScene(window)));
		//scenes.insert(std::make_pair(SCENE_LOBBY, new LobbyScene(window)));
		scenes.insert(std::make_pair(SCENE_GAME, new GameScene(window, recvQueue, sendQueue)));
		
		receiver.start();
		sender.start();
	}

void SceneSelector::run() {
	BaseScene* scene;
	bool done = false;
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

	    //Check exec time and sleep
	    std::clock_t end = clock();
	    double execTime = double(end - begin) / (CLOCKS_PER_SEC/1000);
	    if (execTime < 25) this->sleep(25 - execTime);
	}
}

void SceneSelector::sleep(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

SceneSelector::~SceneSelector() {
	receiver.join();
	sender.join();

	for (auto& it : scenes) {
		delete it.second;
	}
}