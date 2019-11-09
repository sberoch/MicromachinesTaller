#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "TextureCreator.h"
#include "GameObjects.h"
#include <map>

class GameObjects {
private:
	TextureCreator& creator;
	std::map<int, ObjectViewPtr> tracksMap;
	std::map<int, ObjectViewPtr> decorationsMap;
	std::map<int, ObjectViewPtr> carsMap;
	std::map<int, ObjectViewPtr> boostsMap;
	std::map<int, ObjectViewPtr> interactablesMap;
	std::map<int, ObjectViewPtr> miscMap;

public:
	GameObjects(TextureCreator& creator);

	void draw(int cameraX, int cameraY);
	void add(int type, int id, ObjectViewPtr obj);
	void remove(int type, int id);
	ObjectViewPtr getCar(int id);
	ObjectViewPtr getTrack(int id);
	ObjectViewPtr getBoost(int id);
	ObjectViewPtr getInteractable(int id);
	ObjectViewPtr getMisc(int id);

	std::map<int, ObjectViewPtr>& getAllTracks();
	std::map<int, ObjectViewPtr>& getAllCars();
	std::map<int, ObjectViewPtr>& getAllBoosts();
	std::map<int, ObjectViewPtr>& getAllInteractables();
};

#endif // GAME_OBJECTS_H
