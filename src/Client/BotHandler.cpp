#include "BotHandler.h"

BotHandler::BotHandler(GameObjects& gameObjects) :
	gameObjects(gameObjects) {
		lua.open("bot_functions.lua");
	}

void BotHandler::handle() {
	//TODO: ejecutar script de lua pasandole la pista (map de track views) y el auto
}