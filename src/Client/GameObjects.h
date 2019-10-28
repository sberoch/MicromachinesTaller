#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "TextureCreator.h"
#include "GameObjects.h"

class GameObjects {
private:
	TextureCreator& creator;
public:
	GameObjects(TextureCreator& creator);
	//TODO: parameters?
	void addCar();
	void addInteractiveObject();
	void removeInteractiveObject();
};

#endif // GAME_OBJECTS_H
