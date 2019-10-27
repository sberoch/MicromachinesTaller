#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "SdlWindow.h"
#include "SdlTexture.h"
#include "View/BackgroundView.h"
#include "InputHandler.h"
#include "TextureCreator.h"
#include "BaseScene.h"
#include <map>
#include <string>
#include "../Common/Converter.h"
#include "../Common/ServerSnapshot.h"
#include "../Common/Queue.h"
#include "../Common/BlockingQueue.h"

class GameScene : public BaseScene {
private:
	SdlWindow& window;
	bool isDone;

	Queue<ServerSnapshot*>& recvQueue;
	BlockingQueue& sendQueue;

	SdlTexture backgroundTex;
	BackgroundView background;
	InputHandler handler;
	TextureCreator creator;
	std::map<int, ObjectViewPtr> gameObjects;
	Converter conv;
	int cameraX, cameraY;

	//Mock
	int myID;

public:
	GameScene(SdlWindow& window, Queue<ServerSnapshot*>& recvQueue,
		BlockingQueue& sendQueue);
	virtual bool done() override;
	virtual void update() override;
	virtual void draw() override;
	virtual int handle() override;
	virtual ~GameScene() {}
private:
	void loadStage();
	void drawBackground();
	void updateCars(CarList cars);
	void updateGameEvents();
};

#endif // GAME_SCENE_H
