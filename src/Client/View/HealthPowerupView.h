#ifndef HEALTH_POWERUP_VIEW_H
#define HEALTH_POWERUP_VIEW_H

#include "ObjectView.h"

class HealthPowerupView : public ObjectView {
private:
	int frame;
public:
	HealthPowerupView(const SdlTexture& tex);
 	virtual void drawAt(int x, int y) override;
 	virtual ~HealthPowerupView() {}
};

#endif // HEALTH_POWERUP_VIEW_H