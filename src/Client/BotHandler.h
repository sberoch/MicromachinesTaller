#ifndef BOT_HANDLER_H
#define BOT_HANDLER_H

#include "GameObjects.h"

class BotHandler {
private:
	GameObjects& gameObjects;
public:
	BotHandler(GameObjects& gameObjects);
	void handle();
};

#endif // BOT_HANDLER_H
