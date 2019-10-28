#ifndef HEALTH_BAR_FRONT_VIEW_H
#define HEALTH_BAR_FRONT_VIEW_H

#include "ObjectView.h"

class HealthBarFrontView : public ObjectView {
private:
	int health;
public:
	HealthBarFrontView(const SdlTexture& tex);
	virtual void drawAt(int x, int y) override;
	virtual void resize(int newSize) override;
 	virtual ~HealthBarFrontView() {}
};

#endif // HEALTH_BAR_FRONT_VIEW_H
