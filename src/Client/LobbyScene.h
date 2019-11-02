#ifndef LOBBY_SCENE_H
#define LOBBY_SCENE_H

#include "BaseScene.h"
#include "SdlWindow.h"
#include "SdlTexture.h"
#include "Audio.h"
#include "View/BackgroundView.h"

class LobbyScene : public BaseScene {
private:
	SdlWindow& window;
	SdlTexture backgroundLobbyTex;
	BackgroundView backgroundLobby;
	Audio audio;
	SDL_Event e;

	bool _done;
	bool fullscreen;
	int nextScene;
	int xScreen, yScreen;
public:
	LobbyScene(SdlWindow& window);
	virtual bool done() override;
	virtual void update() override;
	virtual void draw() override;
	virtual int handle() override;
private:
	bool insidePlayUserButton(int x, int y);
};

#endif // LOBBY_SCENE_H
