#ifndef BOT_HANDLER_H
#define BOT_HANDLER_H

#include "GameObjects.h"
#include "LuaInterpreter.h"
#include "Audio.h"
#include "../Common/Event/Event.h"
#include "../Common/SafeQueue.h"
#include "../Common/Event/CommandEvent.h"
#include "PlayerDescriptor.h"

class BotHandler {
private:
	GameObjects& gameObjects;
	LuaInterpreter lua;
	Audio& audio;
	SafeQueue<Event*>& sendQueue;
	PlayerDescriptor& player;
	int moveRepeatCounter;

public:
	BotHandler(GameObjects& gameObjects, Audio& audio, 
		SafeQueue<Event*>& sendQueue, PlayerDescriptor& player);
	void loadMap();
	void handle();

};

#endif // BOT_HANDLER_H
