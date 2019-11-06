#include "BotHandler.h"
#include "TextureCreator.h"
#include <iostream>

BotHandler::BotHandler(GameObjects& gameObjects) :
	gameObjects(gameObjects), playerId(-1) {
		lua.open("bot_functions.lua");
}

void BotHandler::setPlayerId(int id) {
	playerId = id;
}

void BotHandler::handle() {
	ObjectViewPtr myCar = gameObjects.getCar(playerId);
	std::cout << "My Car: " << myCar->getX() << ", " << myCar->getY() << std::endl;

	std::map<int, ObjectViewPtr>& tracks = gameObjects.getAllTracks();
	for (auto& it : tracks) {
		std::cout << "Track: " << it.second->getX() << ", " << it.second->getY() << std::endl;
	}
}