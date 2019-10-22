#include "SceneSelector.h"
#include "../Common/Constants.h"
#include "GameScene.h"

SceneSelector::SceneSelector(int xScreen, int yScreen) : 
	window(xScreen, yScreen),
	currentScene(SCENE_GAME) /*TODO: menu*/ {
		//scenes.insert(std::make_pair(SCENE_MENU, new MenuScene(window)));
		//scenes.insert(std::make_pair(SCENE_LOBBY, new LobbyScene(window)));
		scenes.insert(std::make_pair(SCENE_GAME, new GameScene(window)));
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
	    }
	}
}

SceneSelector::~SceneSelector() {
	for (auto& it : scenes) {
		delete it.second;
	}
}