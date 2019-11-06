#ifndef BOT_HANDLER_H
#define BOT_HANDLER_H

#include "GameObjects.h"
#include "LuaInterpreter.h"

class BotHandler {
private:
	GameObjects& gameObjects;
	LuaInterpreter lua;
public:
	BotHandler(GameObjects& gameObjects);
	void handle();
};

#endif // BOT_HANDLER_H
