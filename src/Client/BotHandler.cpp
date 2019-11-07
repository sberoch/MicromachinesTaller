#include "BotHandler.h"
#include "TextureCreator.h"
#include "../Common/Event/CommandEvent.h"
#include <iostream>

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

//TODO: todo esto es medio mock, tengo que llamar una sola vez por ciclo a lua desde c++
void BotHandler::handle() {
	ObjectViewPtr myCar = gameObjects.getCar(playerId);
	if (insideTracks()) {
		//TODO: estoy suponiendo que el car esta siempre en el angulo correcto
		InputEnum mov = (InputEnum) lua.getNextMovement(myCar->getX(), myCar->getY());
		sendQueue.push(new CommandEvent(mov));
	} else {
		audio.playEffect(SFX_CAR_ENGINE);
		sendQueue.push(new CommandEvent(ACCELERATE));
	}
}

bool BotHandler::insideTracks() {
	ObjectViewPtr myCar = gameObjects.getCar(playerId);
	return lua.insideTracks(myCar->getX(), myCar->getY());
}