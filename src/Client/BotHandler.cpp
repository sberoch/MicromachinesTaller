#include "BotHandler.h"
#include "TextureCreator.h"
#include <iostream>

#define CYCLES_UNTIL_MOVE_REPEAT 3

BotHandler::BotHandler(GameObjects& gameObjects, Audio& audio, 
            SafeQueue<Event*>& sendQueue, PlayerDescriptor& player) :
        gameObjects(gameObjects),
        audio(audio),
        sendQueue(sendQueue),
        player(player),
        moveRepeatCounter(0),
        _done(false) {
    lua.open("bot_functions.lua");
}

void BotHandler::loadMap() {
    std::map<int, ObjectViewPtr>& tracks = gameObjects.getAllTracks();
    for (auto it = tracks.rbegin(); it != tracks.rend(); ++it) {
        lua.addToTrackTable(it->second);
    }
    lua.setupInitialValues();
}

void BotHandler::handle(SDL_Event& event) {
    if (moveRepeatCounter > CYCLES_UNTIL_MOVE_REPEAT) {
        moveRepeatCounter = 0;
        ObjectViewPtr myCar = gameObjects.getCar(player.playerId);
        InputEnum mov = (InputEnum) lua.getNextMovement(myCar->getX(), myCar->getY(), myCar->getAngle());
        sendQueue.push(new CommandEvent(mov, player.globalId));

    } else {
        moveRepeatCounter++;
    }

    if (event.type == SDL_KEYDOWN) {
    	SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
    	if (keyEvent.keysym.sym == SDLK_b) {
    		player.isBot = false;
    	}
    }
}

bool BotHandler::done() {
    return _done;
}