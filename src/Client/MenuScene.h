#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "BaseScene.h"
#include "SdlWindow.h"
#include "../Common/SafeQueue.h"
#include "../Common/Event/Event.h"
#include "SdlTexture.h"
#include "Audio.h"
#include "View/BackgroundView.h"

class MenuScene : public BaseScene {
private:
	SdlWindow& window;
	SafeQueue<std::shared_ptr<Event>>& sendQueue;
	SdlTexture backgroundMenuTex;
	BackgroundView backgroundMenu;
	Audio audio;
	SDL_Event e;
	bool _done;
	bool fullscreen;
	Scene nextScene;
	int xScreen, yScreen;
public:
	MenuScene(SdlWindow& window, SafeQueue<std::shared_ptr<Event>>& sendQueue);
	bool done() override;
	void update() override;
	void draw() override;
	Scene handle() override;
	~MenuScene() override = default;
private:
	bool insidePlayButton(int x, int y);
	bool insideQuitButton(int x, int y);
};

#endif // MENU_SCENE_H
