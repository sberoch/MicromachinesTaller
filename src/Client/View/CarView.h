#ifndef CAR_VIEW_H
#define CAR_VIEW_H

#include "ObjectView.h"

class CarView : public ObjectView {
private:
	int angle;
public:
	CarView(const SdlTexture& tex, const int& angle);
 	virtual void drawAt(int x, int y) override;
 	virtual void move(int x, int y) override;
 	virtual void setRotation(int angle) override;
 	virtual ~CarView() {}
};

#endif // CAR_VIEW_H