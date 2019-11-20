#ifndef BASE_SCENE_H
#define BASE_SCENE_H

#include <SDL2/SDL_events.h>

class BaseScene {
public:
	virtual bool done() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual int handle(SDL_Event& event) = 0;
	virtual ~BaseScene() {}
};

#endif // BASE_SCENE_H