#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "SdlWindow.h"
#include "SdlTexture.h"
#include "View/BackgroundView.h"
#include "InputHandler.h"
#include "TextureCreator.h"
#include "PlayerDisplay.h"
#include "GameObjects.h"
#include "BotHandler.h"
#include "BaseScene.h"
#include "Audio.h"
#include <map>
#include <string>
#include "../Common/Converter.h"
#include "../Common/ServerSnapshot.h"
#include "../Common/Event/Event.h"
#include "../Common/SafeQueue.h"
#include "../Common/Queue.h"


class GameScene : public BaseScene {
private:
	SdlWindow& window;
	Audio audio;
	bool isDone;

	Queue<ServerSnapshot*>& recvQueue; 
	SafeQueue<Event*>& sendQueue;

	SdlTexture backgroundTex;
	BackgroundView background;
	PlayerDisplay display;

	InputHandler handler;
	TextureCreator creator;

	GameObjects gameObjects;
	BotHandler bot;

	Converter conv;
	int cameraX, cameraY;
	int xScreen, yScreen;

	//Mock
	int myID;
	bool isBot;

public:
	GameScene(SdlWindow& window, Queue<ServerSnapshot*>& recvQueue, 
					SafeQueue<Event*>& sendQueue);
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
