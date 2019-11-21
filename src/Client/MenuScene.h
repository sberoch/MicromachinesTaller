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
	SafeQueue<Event*>& sendQueue;
	SdlTexture backgroundMenuTex;
	BackgroundView backgroundMenu;
	Audio audio;
	SDL_Event e;
	bool _done;
	bool fullscreen;
	Scene nextScene;
	int xScreen, yScreen;
public:
	MenuScene(SdlWindow& window, SafeQueue<Event*>& sendQueue);
	virtual bool done() override;
	virtual void update() override;
	virtual void draw() override;
	virtual Scene handle() override;
	virtual ~MenuScene() {}
private:
	bool insidePlayButton(int x, int y);
	bool insideQuitButton(int x, int y);
};

#endif // MENU_SCENE_H
