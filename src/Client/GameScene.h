#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "SdlWindow.h"
#include "SdlTexture.h"
#include "BackgroundView.h"
#include "InputHandler.h"
#include "TextureCreator.h"
#include "BaseScene.h"
#include <map>
#include "../Common/Converter.h"

class GameScene : public BaseScene {
private:
	SdlWindow& window;
	bool isDone;

	SdlTexture backgroundTex;
	BackgroundView background;
	InputHandler handler;
	TextureCreator creator;
	std::map<int, ObjectViewPtr> gameObjects;
	Converter conv;
public:
	GameScene(SdlWindow& window);
	virtual bool done() override;
	virtual void update() override;
	virtual void draw() override;
	virtual int handle() override;
	virtual ~GameScene() {}
private:
	void loadStage();
	void drawBackground();
};

#endif // GAME_SCENE_H
