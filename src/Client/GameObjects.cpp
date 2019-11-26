#include "GameObjects.h"
#include <iostream>

GameObjects::GameObjects(TextureCreator& creator) :
	creator(creator),
	explosionsCounter(0) {}


void GameObjects::draw(int cameraX, int cameraY) {
	for (auto& it : tracksMap) {
		it.second->drawAt(cameraX, cameraY);
	}
	for (auto& it : decorationsMap) {
		it.second->drawAt(cameraX, cameraY);
	}
	for (auto& it : interactablesMap) {
		it.second->drawAt(cameraX, cameraY);
	}
	for (auto& it : carsMap) {
		if (drawableCarsMap.at(it.first))
			it.second->drawAt(cameraX, cameraY);
	}
	for (auto& it : miscMap) {
		it.second->drawAt(cameraX, cameraY);
	}
	for (auto& it : boostsMap) {
		it.second->drawAt(cameraX, cameraY);
	}
}

void GameObjects::add(int type, int id, const ObjectViewPtr& obj) {
	switch(type) {
		case TYPE_STRAIGHT_TRACK: case TYPE_CURVE_TRACK: {
			tracksMap.insert(std::make_pair(id, obj));
			break;
		}
		case TYPE_HEALTH_POWERUP: case TYPE_BOOST_POWERUP: {
			boostsMap.insert(std::make_pair(id, obj));
			break;
		}
		case TYPE_ROCK: case TYPE_OIL: case TYPE_MUD: {
			interactablesMap.insert(std::make_pair(id, obj));
			break;
		}
		case TYPE_CAR_RED: case TYPE_CAR_BLUE: case TYPE_CAR_YELLOW: case TYPE_CAR_GREEN: {
			carsMap.insert(std::make_pair(id, obj));
			drawableCarsMap.insert(std::make_pair(id, true));
			break;
		}
		case TYPE_EXPLOSION: {
			miscMap.insert(std::make_pair(explosionsCounter, obj));
			explosionsCounter++;
			break;
		}
		case TYPE_START_LINE: {
			decorationsMap.insert(std::make_pair(id, obj));
			break;
		}
		default:
			break;
	}
}

void GameObjects::remove(int type, int id) {
	switch(type) {
		case TYPE_STRAIGHT_TRACK: case TYPE_CURVE_TRACK: {
			tracksMap.erase(id);
			break;
		}
		case TYPE_HEALTH_POWERUP: case TYPE_BOOST_POWERUP: {
			boostsMap.erase(id);
			break;
		}
		case TYPE_ROCK: case TYPE_OIL: case TYPE_MUD: {
			interactablesMap.erase(id);
			break;
		}
		case TYPE_CAR: case TYPE_CAR_RED: case TYPE_CAR_BLUE: case TYPE_CAR_YELLOW: case TYPE_CAR_GREEN: {
			carsMap.erase(id);
			drawableCarsMap.erase(id);
			break;
		}
		case TYPE_EXPLOSION: {
			miscMap.erase(id);
			break;
		}
		case TYPE_START_LINE: {
			decorationsMap.erase(id);
			break;
		}
		default:
			break;
	}
}

ObjectViewPtr GameObjects::getCar(int id) {
	return carsMap.at(id);
}

ObjectMap& GameObjects::getAllTracks() {
	return tracksMap;
}

void GameObjects::hideCar(int playerId) {
	drawableCarsMap.at(playerId) = false;
}

void GameObjects::showCar(int playerId) {
	if (drawableCarsMap.count(playerId)) {
		drawableCarsMap.at(playerId) = true;
	}
}

void GameObjects::clear() {
	tracksMap.clear();
	decorationsMap.clear();
	carsMap.clear();
	drawableCarsMap.clear();
	boostsMap.clear();
	interactablesMap.clear();
	miscMap.clear();
}

