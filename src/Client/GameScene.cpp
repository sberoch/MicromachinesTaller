#include "GameScene.h"
#include "../Common/json.hpp"
#include "../Common/Constants.h"
#include <iostream>

using json = nlohmann::json;

GameScene::GameScene(SdlWindow& window, Queue<SnapshotEvent*>& recvQueue, 
					SafeQueue<Event*>& sendQueue, PlayerDescriptor& player) : 
	window(window),
	recorder(REC_SIZE_HOR, REC_SIZE_VERT),
	isDone(false),
	recvQueue(recvQueue),
	sendQueue(sendQueue),
	player(player),

	backgroundTex("background.png", window),
	background(backgroundTex),
	display(window),
	
	handler(window, audio, recorder, sendQueue, player),
	creator(window),

	gameObjects(creator),
	bot(gameObjects, audio, recorder, sendQueue, player),
	conv(PIXELS_PER_BLOCK), 
	xScreen(0),
	yScreen(0),
	nextScene(SCENE_GAME),
	isGameOver(false),
	isMapReady(false) {}

bool GameScene::done() {
	return isDone;
}

void GameScene::update() {
	audio.playMusic();
	window.getWindowSize(&xScreen, &yScreen);

	SnapshotEvent* snap;
	while (recvQueue.pop(snap)) {
		updateCars(snap->getCars());
		updateGameEvents(snap->getGameEvents());
		delete snap;
	}
}

void GameScene::updateCars(CarStructList cars) {
	for (auto& car : cars) {
		ObjectViewPtr carView = gameObjects.getCar(car.id);
		carView->setRotation(car.angle);
		carView->move(conv.blockToPixel(car.x),
					  conv.blockToPixel(car.y));
		if (car.id == player.playerId) {
			display.update(xScreen/2 - conv.blockToPixel(car.x),
						   yScreen/2 - conv.blockToPixel(car.y),
						   car.health);
		}
	}	
}

void GameScene::updateGameEvents(GameEventsList gameEvents) {
	for (auto& gameEvent : gameEvents) {
 		switch(gameEvent.eventType) {
			case ADD: addObject(gameEvent); break;
			case REMOVE: removeObject(gameEvent); break;
			case MAP_LOAD_FINISHED: isMapReady = true; bot.loadMap(); break;
			case MUD_SPLAT: display.showMudSplat(); break;
			case GAME_OVER: gameOver(gameEvent); break;
			default: break;
		}
	}
}

void GameScene::addObject(GameEventStruct gameEvent) {
	ObjectViewPtr ov = creator.create(gameEvent.objectType, 
										conv.blockToPixel(gameEvent.x), 
										conv.blockToPixel(gameEvent.y), 
										gameEvent.angle);
	gameObjects.add(gameEvent.objectType, gameEvent.id, ov);
	if (gameEvent.objectType == TYPE_EXPLOSION) {
		audio.playEffect(SFX_CAR_EXPLOSION);
	}
}

void GameScene::removeObject(GameEventStruct gameEvent) {
	gameObjects.remove(gameEvent.objectType, gameEvent.id);
}

void GameScene::gameOver(GameEventStruct gameEvent) {
	if (gameEvent.id == player.playerId) {
		nextScene = SCENE_END;
	}
}

void GameScene::draw() {
	window.fill();
	drawBackground();
	gameObjects.draw(display.cam_x, display.cam_y);
	display.draw();
	window.render();
}

Scene GameScene::handle() {
	if (isMapReady) {
		if (player.isBot) {
			bot.handle();
			if (bot.done()) {
				isDone = true;
			}

		} else {
			handler.handle();
			if (handler.done()) {
				isDone = true;
			}
		}
	}
	return nextScene;
}

void GameScene::drawBackground() { 
	background.setDims(xScreen, yScreen);
	for(int i = 0; i < 5; ++i) {
		for(int j = 0; j < 5; ++j) {
			background.drawAt(
				-xScreen*2 + xScreen*i + display.cam_x,
				-yScreen + yScreen*j + display.cam_y);
		}
	}
}