#include "GameScene.h"
#include "../Common/json.hpp"
#include "../Common/Constants.h"

#include <SDL2/SDL.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

GameScene::GameScene(SdlWindow& window, Queue<ServerSnapshot*>& recvQueue, 
					BlockingQueue& sendQueue) : 
	window(window),
	isDone(false),
	recvQueue(recvQueue),
	sendQueue(sendQueue),	
	backgroundTex("background.png", window),
	background(backgroundTex),
	handler(window, sendQueue),
	creator(window),
	conv(50) {
		window.fill();

		//Mock
		myID = 11;
		loadStage();
}

bool GameScene::done() {
	return isDone;
}

void GameScene::update() {
	ServerSnapshot* snap;
	if (recvQueue.get(snap)) {
		updateCars(snap->getCars());
		updateGameEvents();
		delete snap;
	}
}

void GameScene::updateCars(CarList cars) {
	for (auto& car : cars) {
		ObjectViewPtr carView = gameObjects.at(car.id);
		carView->setRotation(car.angle);
		carView->move(conv.blockToPixel(car.x),
					  conv.blockToPixel(car.y));
		std::cout << "\nx: " << conv.blockToPixel(car.x);
		std::cout << "\ny: " << conv.blockToPixel(car.x);
		std::cout << "\nangle: " << car.angle;
		std::cout << "\nid: " << car.id;
		if (car.id == myID) {
			//cameraX = conv.blockToPixel(car.x);
			//cameraY = conv.blockToPixel(car.y);
		}
	}	
}

void GameScene::updateGameEvents() {

}

void GameScene::draw() {
	window.fill();
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	drawBackground();
	for (auto& it : gameObjects) {
		//TODO: change this to support camera.
		it.second->drawAt(0, 0);
	}
	window.render();
}

int GameScene::handle() {
	handler.handle();
	if (handler.done()) {
		isDone = true;
	}
	//TODO: change this to support a final scene.
	return SCENE_GAME;
}

void GameScene::loadStage() {
	int id, x, y, angle;
	std::ifstream i("scene.json");
	json j; i >> j;

	json objects = j["objects"];
	for (auto& obj : objects) {
		id = obj["type"].get<int>();
		x = conv.blockToPixel(obj["x"].get<int>());
		y = conv.blockToPixel(obj["y"].get<int>());
		angle = obj["angle"].get<int>();
		ObjectViewPtr ov = creator.create(id, x, y, angle);
		gameObjects.insert(std::make_pair(ov->getId(), ov));
		if (ov->getId() == myID) {
			//Center camera in car
			//int screenX, screenY;
			//window.getWindowSize(&screenX, &screenY);
			//cameraX = screenX/2 - x;
			//cameraY = screenY/2 - y;
		}
	}
}

void GameScene::drawBackground() {
	int xScreen, yScreen; 
	window.getWindowSize(&xScreen, &yScreen); //Fullscreen
	background.setDims(xScreen, yScreen);
	for(int i = 0; i < 5; ++i) {
		for(int j = 0; j < 3; ++j) {
			background.drawAt(-xScreen*2 + xScreen*i,
						-yScreen/2 + yScreen*j);
		}
	}
}