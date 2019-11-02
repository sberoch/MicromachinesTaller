#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "TextureCreator.h"
#include "GameObjects.h"
#include <map>

//TODO: separar mapas segun tipos de objetos (pista, autos, interactuables)
//		y se va a hacer get() con tipo e id

class GameObjects {
private:
	TextureCreator& creator;
	std::map<int, ObjectViewPtr> objectsMap;

	//TODO: terminar
	std::map<int, ObjectViewPtr> cars;
	std::map<int, ObjectViewPtr> tracks;
	std::map<int, ObjectViewPtr> badInteractiveObjects;
	std::map<int, ObjectViewPtr> goodInteractiveObjects;

public:
	GameObjects(TextureCreator& creator);

	//TODO: no se si queda esto
	void draw(int cameraX, int cameraY);
	void add(int type, std::pair<int, ObjectViewPtr> obj);
	ObjectViewPtr get(int id);
	
};

#endif // GAME_OBJECTS_H
