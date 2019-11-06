#include "GameObjects.h"
#include <iostream>

GameObjects::GameObjects(TextureCreator& creator) :
	creator(creator) {}


void GameObjects::draw(int cameraX, int cameraY) {
	for (auto& it : tracksMap) {
		it.second->drawAt(cameraX, cameraY);
	}
	for (auto& it : interactablesMap) {
		it.second->drawAt(cameraX, cameraY);
	}
	for (auto& it : carsMap) {
		it.second->drawAt(cameraX, cameraY);
	}
	for (auto& it : miscMap) {
		it.second->drawAt(cameraX, cameraY);
	}
	for (auto& it : boostsMap) {
		it.second->drawAt(cameraX, cameraY);
	}
}

//TODO: refactor con mapa
void GameObjects::add(int type, int id, ObjectViewPtr obj) {
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
			tracksMap.insert(std::make_pair(id, obj));
			break;
		}
		case TYPE_CAR_RED: case TYPE_CAR_BLUE: case TYPE_CAR_YELLOW: case TYPE_CAR_GREEN: {
			carsMap.insert(std::make_pair(id, obj));
			break;
		}
		case TYPE_EXPLOSION: {
			miscMap.insert(std::make_pair(id, obj));
			break;
		}
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
			tracksMap.erase(id);
			break;
		}
		case TYPE_CAR_RED: case TYPE_CAR_BLUE: case TYPE_CAR_YELLOW: case TYPE_CAR_GREEN: {
			carsMap.erase(id);
			break;
		}
		case TYPE_EXPLOSION: {
			miscMap.erase(id);
			break;
		}
	}
}

ObjectViewPtr GameObjects::getCar(int id) {
	ObjectViewPtr ret = carsMap.at(id);
	if (ret == nullptr) 
		throw std::runtime_error("GameObjects: object not found");
	return ret;
}

ObjectViewPtr GameObjects::getBoost(int id) {
	ObjectViewPtr ret = boostsMap.at(id);
	if (ret == nullptr) 
		throw std::runtime_error("GameObjects: object not found");
	return ret;
}

ObjectViewPtr GameObjects::getInteractable(int id) {
	ObjectViewPtr ret = interactablesMap.at(id);
	if (ret == nullptr) 
		throw std::runtime_error("GameObjects: object not found");
	return ret;
}

ObjectViewPtr GameObjects::getTrack(int id) {
	ObjectViewPtr ret = tracksMap.at(id);
	if (ret == nullptr) 
		throw std::runtime_error("GameObjects: object not found");
	return ret;
}

ObjectViewPtr GameObjects::getMisc(int id) {
	ObjectViewPtr ret = miscMap.at(id);
	if (ret == nullptr) 
		throw std::runtime_error("GameObjects: object not found");
	return ret;
}
