#ifndef BOT_HANDLER_H
#define BOT_HANDLER_H

#include "GameObjects.h"
#include "LuaInterpreter.h"

class BotHandler {
private:
	GameObjects& gameObjects;
	LuaInterpreter lua;
	int playerId;

public:
	BotHandler(GameObjects& gameObjects);
	void setPlayerId(int id);
	void handle();

private:
	bool insideTracks();
};

#endif // BOT_HANDLER_H
