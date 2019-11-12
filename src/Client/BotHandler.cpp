#include "BotHandler.h"
#include "TextureCreator.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

#define CYCLES_UNTIL_MOVE_REPEAT 10

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
	std::clock_t begin = clock();

	ObjectViewPtr myCar = gameObjects.getCar(playerId);
	InputEnum mov = (InputEnum) lua.getNextMovement(myCar->getX(), myCar->getY(), myCar->getAngle());
	bool hasAccelerated = (prevMov == mov) && (prevMov == ACCELERATE);

	if (hasAccelerated || moveRepeatCounter > CYCLES_UNTIL_MOVE_REPEAT) {
		prevMov = mov;
		sendQueue.push(new CommandEvent(mov, playerId));
	}
	moveRepeatCounter++;


	std::clock_t end = clock();
	double execTime = double(end - begin) / (CLOCKS_PER_SEC/1000);
	if (execTime < 10) this->sleep(10 - execTime);
}

void BotHandler::sleep(int millisec) {
	std::this_thread::sleep_for(std::chrono::milliseconds(millisec));
}