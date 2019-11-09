#ifndef BOT_HANDLER_H
#define BOT_HANDLER_H

#include "GameObjects.h"
#include "LuaInterpreter.h"
#include "Audio.h"
#include "../Common/Event/Event.h"
#include "../Common/SafeQueue.h"

class BotHandler {
private:
	GameObjects& gameObjects;
	LuaInterpreter lua;
	Audio& audio;
	SafeQueue<Event*>& sendQueue;
	int playerId;

public:
	BotHandler(GameObjects& gameObjects, Audio& audio, SafeQueue<Event*>& sendQueue);
	void setPlayerId(int id);
	void handle();

private:
	void sleep(int millisec);
};

#endif // BOT_HANDLER_H
