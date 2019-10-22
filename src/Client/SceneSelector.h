#ifndef SCENE_SELECTOR_H
#define SCENE_SELECTOR_H

#include "SdlWindow.h"
#include "BaseScene.h"
#include <map>

class SceneSelector {
private:
	SdlWindow window;
	std::map<int, BaseScene*> scenes;
	int currentScene;
public:
	SceneSelector(int xScreen, int yScreen);
	void run();
	~SceneSelector();
};

#endif // SCENE_SELECTOR_H