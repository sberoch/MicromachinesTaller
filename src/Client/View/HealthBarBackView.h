#ifndef HEALTH_BAR_BACK_VIEW_H
#define HEALTH_BAR_BACK_VIEW_H

#include "ObjectView.h"

class HealthBarBackView : public ObjectView {
public:
	HealthBarBackView(const SdlTexture& tex);
	virtual void drawAt(int x, int y) override;
 	virtual ~HealthBarBackView() {}
};

#endif // HEALTH_BAR_BACK_VIEW_H
