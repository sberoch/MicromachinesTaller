#include "BotHandler.h"
#include "TextureCreator.h"
#include <iostream>

#define CYCLES_UNTIL_MOVE_REPEAT 1

BotHandler::BotHandler(GameObjects& gameObjects, Audio& audio, SafeQueue<Event*>& sendQueue, int& playerId) :
	gameObjects(gameObjects), 
	audio(audio), 
	sendQueue(sendQueue), 
	playerId(playerId),
	moveRepeatCounter(0) {
		lua.open("bot_functions.lua");
}

void BotHandler::loadMap() {
	std::map<int, ObjectViewPtr>& tracks = gameObjects.getAllTracks();
	for (auto it = tracks.rbegin(); it != tracks.rend(); ++it) {
        lua.addToTrackTable(it->second);
    }
	lua.setupInitialValues();
}

void BotHandler::handle() {
	if (moveRepeatCounter > CYCLES_UNTIL_MOVE_REPEAT) {
		moveRepeatCounter = 0;
		ObjectViewPtr myCar = gameObjects.getCar(playerId);
		InputEnum mov = (InputEnum) lua.getNextMovement(myCar->getX(), myCar->getY(), myCar->getAngle());
		sendQueue.push(new CommandEvent(mov, playerId));

	} else {
		moveRepeatCounter++;
	}
}