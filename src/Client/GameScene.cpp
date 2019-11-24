#include "GameScene.h"
#include <iostream>

using json = nlohmann::json;

GameScene::GameScene(SdlWindow& window, SafeQueue<std::shared_ptr<SnapshotEvent>>& recvQueue,
					 SafeQueue<std::shared_ptr<Event>>& sendQueue, PlayerDescriptor& player) :
	window(window),
	recorder(window),
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
	isMapReady(false),
	carExploded(false) {}

bool GameScene::done() {
	return isDone;
}

void GameScene::update() {
    nextScene = SCENE_GAME;
    isGameOver = false;
	audio.playMusic();
	window.getWindowSize(&xScreen, &yScreen);

	//If my car exploded, check if it is ready to draw again.
	if(!display.hasMyCarExploded()) {
		gameObjects.showCar(player.playerId);
		carExploded = false;
	}

	std::shared_ptr<SnapshotEvent> snap;
	while (recvQueue.get(snap)) {
		updateCars(snap->getCars());
		updateGameEvents(snap->getGameEvents());
	}
}

void GameScene::updateCars(const CarStructList& cars) {
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


void GameScene::updateGameEvents(const GameEventsList& gameEvents) {
	for (auto& gameEvent : gameEvents) {
 		if (!isGameOver) {
 			switch(gameEvent.eventType) {
				case ADD: addObject(gameEvent); break;
				case REMOVE: removeObject(gameEvent); break;
				case MAP_LOAD_FINISHED: isMapReady = true; bot.loadMap(); break;
				case MUD_SPLAT: showMudSplat(gameEvent); break;
				case GAME_OVER: gameOver(gameEvent); break;
				case LAP_COMPLETED: lapCompleted(gameEvent); break;
				default: break;
			}
 		}
	}
}

void GameScene::showMudSplat(GameEventStruct gameEvent){
    if (gameEvent.id == player.playerId) {
        display.showMudSplat();
    }
}

void GameScene::addObject(GameEventStruct gameEvent) {
	ObjectViewPtr ov = creator.create((ObjectType) gameEvent.objectType,
										conv.blockToPixel(gameEvent.x), 
										conv.blockToPixel(gameEvent.y), 
										gameEvent.angle);
	gameObjects.add(gameEvent.objectType, gameEvent.id, ov);
	if (gameEvent.objectType == TYPE_EXPLOSION) {
		carExplosion(gameEvent);
	}
}

void GameScene::removeObject(GameEventStruct gameEvent) {
	gameObjects.remove(gameEvent.objectType, gameEvent.id);
}

void GameScene::gameOver(GameEventStruct gameEvent) {
	if (gameEvent.id == player.playerId) {
		nextScene = SCENE_END;
		display.clear();
		gameObjects.clear();
		audio.stopMusic();
		isGameOver = true;
		isMapReady = false;
	}
}

void GameScene::lapCompleted(GameEventStruct gameEvent) {
	if (gameEvent.id == player.playerId) {
		//Angle is being used here for the lap number
		display.setLapNumber(gameEvent.angle);
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
	if (isMapReady && !carExploded) {
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
	for(int i = 0; i < 20; ++i) {
		for(int j = 0; j < 20; ++j) {
			background.drawAt(
				-xScreen*2 + xScreen*i + display.cam_x,
				-yScreen + yScreen*j + display.cam_y);
		}
	}
}

void GameScene::carExplosion(GameEventStruct gameEvent) {
	if (gameEvent.id == player.playerId) {
			//Center the camera in the explosion.
			display.carExploded(xScreen/2 - conv.blockToPixel(gameEvent.x),
								yScreen/2 - conv.blockToPixel(gameEvent.y));
			//Hide the exploded car.
			gameObjects.hideCar(player.playerId);
			//Remove its movement.
			carExploded = true;

	}
	audio.playEffect(SFX_CAR_EXPLOSION);
}


