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
	bool _done;
public:
	BotHandler(GameObjects& gameObjects, Audio& audio, 
		SafeQueue<Event*>& sendQueue, PlayerDescriptor& player);
	bool done();
	void loadMap();
	void handle(SDL_Event& event);

};

#endif // BOT_HANDLER_H
