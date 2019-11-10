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
#include "../Common/Event/SnapshotEvent.h"
#include "../Common/Event/Event.h"
#include "../Common/SafeQueue.h"
#include "../Common/Queue.h"


class GameScene : public BaseScene {
private:
	SdlWindow& window;
	Audio audio;
	bool isDone;
	int myID;

	Queue<SnapshotEvent*>& recvQueue; 
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
	int nextScene;

	bool isBot;
	bool isGameOver;

public:
	GameScene(SdlWindow& window, Queue<SnapshotEvent*>& recvQueue, 
					SafeQueue<Event*>& sendQueue);
	virtual bool done() override;
	virtual void update() override;
	virtual void draw() override;
	virtual int handle() override;
	virtual ~GameScene() {}
private:
	void drawBackground();

	void updateCars(CarList cars);
	void updateGameEvents(GameEventsList gameEvents);
	void addObject(GameEventStruct gameEvent);
	void removeObject(GameEventStruct gameEvent);
};

#endif // GAME_SCENE_H
