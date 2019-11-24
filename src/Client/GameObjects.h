#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "TextureCreator.h"
#include "GameObjects.h"
#include <map>

typedef std::map<int, ObjectViewPtr> ObjectMap;

class GameObjects {
private:
	TextureCreator& creator;
	ObjectMap tracksMap;
	ObjectMap decorationsMap;
	ObjectMap carsMap;
	ObjectMap boostsMap;
	ObjectMap interactablesMap;
	ObjectMap miscMap;

	std::map<int, bool> drawableCarsMap;

	int explosionsCounter;

public:
	GameObjects(TextureCreator& creator);

	void draw(int cameraX, int cameraY);
	void add(int type, int id, const ObjectViewPtr& obj);
	void remove(int type, int id);
	ObjectViewPtr getCar(int id);
	ObjectViewPtr getTrack(int id);
	ObjectViewPtr getBoost(int id);
	ObjectViewPtr getInteractable(int id);
	ObjectViewPtr getMisc(int id);

	ObjectMap& getAllTracks();
	ObjectMap& getAllCars();
	ObjectMap& getAllBoosts();
	ObjectMap& getAllInteractables();

	void hideCar(int playerId);
	void showCar(int playerId);
	void clear();
};

#endif // GAME_OBJECTS_H
