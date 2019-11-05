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

public:
	GameObjects(TextureCreator& creator);
	//TODO: parameters?
	void addInteractiveObject();
	void removeInteractiveObject();

	//TODO: no se si queda esto
	void draw(int cameraX, int cameraY);
	void add(std::pair<int, ObjectViewPtr> obj);
	ObjectViewPtr get(int id);
	
};

#endif // GAME_OBJECTS_H
