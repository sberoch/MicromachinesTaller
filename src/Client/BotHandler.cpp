#include "BotHandler.h"
#include "TextureCreator.h"
#include "../Common/Constants.h"
#include <iostream>

#define CYCLES_UNTIL_MOVE_REPEAT 1

BotHandler::BotHandler(GameObjects& gameObjects, Audio& audio, ScreenRecorder& recorder,
					   SafeQueue<std::shared_ptr<Event>>& sendQueue, PlayerDescriptor& player) :
        gameObjects(gameObjects),
        audio(audio),
        recorder(recorder),
        sendQueue(sendQueue),
        player(player),
        moveRepeatCounter(0),
        _done(false) {
    lua.open((MISC_DIR + std::string("bot_functions.lua")).c_str());
}

void BotHandler::loadMap() {
    std::map<int, ObjectViewPtr>& tracks = gameObjects.getAllTracks();
    for (auto it = tracks.rbegin(); it != tracks.rend(); ++it) {
        lua.addToTrackTable(it->second);
    }
    lua.setupInitialValues();
}

void BotHandler::handle() {
    handleBotNextMovement();
    handleOtherEvents();
}

void BotHandler::handleBotNextMovement() {
    if (moveRepeatCounter > CYCLES_UNTIL_MOVE_REPEAT) {
        moveRepeatCounter = 0;

        ObjectViewPtr myCar = gameObjects.getCar(player.playerId);
        InputEnum mov = (InputEnum) lua.getNextMovement(myCar->getX(), myCar->getY(), myCar->getAngle());
        if (mov == ACCELERATE) {
            audio.playEffect(SFX_CAR_ENGINE);
        }

        std::shared_ptr<Event> cmd(new CommandEvent(mov, player.globalId));
        sendQueue.push(cmd);

    } else {
        moveRepeatCounter++;
    }
}

void BotHandler::handleOtherEvents() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            _done = true;
        } else if (event.type == SDL_KEYDOWN) {
            SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
            if (keyEvent.keysym.sym == SDLK_b) {
                player.isBot = false;

            } else if (keyEvent.keysym.sym == SDLK_v) {
                if (!recorder.recording()) {
                    recorder.start();
                } else {
                    recorder.close();
                }
            }
        }
    }
}

bool BotHandler::done() {
    return _done;
}