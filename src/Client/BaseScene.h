#ifndef BASE_SCENE_H
#define BASE_SCENE_H

#include "../Common/Constants.h"

class BaseScene {
public:
	virtual bool done() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual Scene handle() = 0;
	virtual ~BaseScene() {}
};

#endif // BASE_SCENE_H