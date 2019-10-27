#ifndef OBJECT_VIEW
#define OBJECT_VIEW

#include "Area.h"
#include "SdlTexture.h"
#include <vector>

class ObjectView {
protected:
	int id;
	SdlTexture texture;
	std::vector<Area> clips;
	int initialX, initialY;
	int frame;
	int horizontalScale;
	int verticalScale;

public:
	virtual void drawAt(int x, int y) = 0;
	virtual void setState(int state);
	virtual void move(int x, int y);
	virtual void setRotation(int angle);
	virtual void flip(int flip);
	void setInitialPos(int x, int y);
	void setId(int id);
	int getId();
	virtual ~ObjectView() {}
};

#endif