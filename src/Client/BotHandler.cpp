#include "BotHandler.h"
#include "TextureCreator.h"
#include "../Common/Event/CommandEvent.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

BotHandler::BotHandler(GameObjects& gameObjects, Audio& audio, SafeQueue<Event*>& sendQueue) :
	gameObjects(gameObjects), audio(audio), sendQueue(sendQueue), playerId(-1) {
		lua.open("bot_functions.lua");
}

void BotHandler::setPlayerId(int id) {
	playerId = id;

	//TODO: va aca?
	std::map<int, ObjectViewPtr>& tracks = gameObjects.getAllTracks();
	for (auto it = tracks.rbegin(); it != tracks.rend(); ++it) {
        lua.addToTrackTable(it->second);
    }
	lua.printTrackTable();
}

void BotHandler::handle() {
	std::clock_t begin = clock();

	InputEnum prevMov = STOP_TURNING_LEFT;
	ObjectViewPtr myCar = gameObjects.getCar(playerId);
	InputEnum mov = (InputEnum) lua.getNextMovement(myCar->getX(), myCar->getY(), myCar->getAngle());
	if (mov != prevMov) {
		sendQueue.push(new CommandEvent(mov));
		prevMov = mov;
	}

	std::clock_t end = clock();
	double execTime = double(end - begin) / (CLOCKS_PER_SEC/1000);
	if (execTime < 100) this->sleep(100 - execTime);
}

void BotHandler::sleep(int millisec) {
	std::this_thread::sleep_for(std::chrono::milliseconds(millisec));
}