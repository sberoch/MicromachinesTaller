#ifndef BOOST_POWERUP_VIEW_H
#define BOOST_POWERUP_VIEW_H

#include "ObjectView.h"

class BoostPowerupView : public ObjectView {
private:
	int frame;
public:
	BoostPowerupView(const SdlTexture& tex);
 	virtual void drawAt(int x, int y) override;
 	virtual ~BoostPowerupView() {}
};

#endif // BOOST_POWERUP_VIEW_H