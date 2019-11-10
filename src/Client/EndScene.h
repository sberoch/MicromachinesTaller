#ifndef END_SCENE_H
#define END_SCENE_H

#include "BaseScene.h"
#include "SdlWindow.h"
#include "SdlTexture.h"
#include "View/BackgroundView.h"

class EndScene : public BaseScene {
private:
	SdlWindow& window;
	SdlTexture backgroundEndTex;
	BackgroundView backgroundEnd;

	SDL_Event e;
	bool _done;
	bool fullscreen;
	int xScreen, yScreen;
public:
	EndScene(SdlWindow& window);
	virtual bool done() override;
	virtual void update() override;
	virtual void draw() override;
	virtual int handle() override;
	virtual ~EndScene() {}
private:
	bool insideQuitButton(int x, int y);
};

#endif // END_SCENE_H
