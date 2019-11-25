#ifndef BOT_HANDLER_H
#define BOT_HANDLER_H

#include "GameObjects.h"
#include "LuaInterpreter.h"
#include "Audio.h"
#include "../Common/Event/Event.h"
#include "../Common/SafeQueue.h"
#include "../Common/Event/CommandEvent.h"
#include "PlayerDescriptor.h"
#include "ScreenRecorder.h"

class BotHandler {
private:
	GameObjects& gameObjects;
	LuaInterpreter lua;
	Audio& audio;
	ScreenRecorder& recorder;
	SafeQueue<std::shared_ptr<Event>>& sendQueue;
	PlayerDescriptor& player;
	int moveRepeatCounter;

	SDL_Event event;
	bool _done;
public:
	BotHandler(GameObjects& gameObjects, Audio& audio, ScreenRecorder& recorder,
			   SafeQueue<std::shared_ptr<Event>>& sendQueue, PlayerDescriptor& player);
	bool done();
	void loadMap();
	void handle();

private:
	void handleBotNextMovement();
	void handleOtherEvents();

};

#endif // BOT_HANDLER_H
