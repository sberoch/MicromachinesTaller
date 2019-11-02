#include "GameObjects.h"

GameObjects::GameObjects(TextureCreator& creator) :
	creator(creator) {}

void GameObjects::addInteractiveObject() {

}

void GameObjects::removeInteractiveObject() {

}

void GameObjects::draw(int cameraX, int cameraY) {
	for (auto& it : objectsMap) {
		it.second->drawAt(cameraX, cameraY);
	}
}

void GameObjects::add(std::pair<int, ObjectViewPtr> obj) {
	objectsMap.insert(obj);
}

ObjectViewPtr GameObjects::get(int id) {
	ObjectViewPtr ret = objectsMap.at(id);
	if (ret == nullptr) 
		throw std::runtime_error("GameObjects: object not found");
	return ret;
}

