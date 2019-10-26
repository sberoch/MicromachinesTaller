#ifndef OIL_VIEW_H
#define OIL_VIEW_H

#include "ObjectView.h"

class OilView : public ObjectView {
private:
	int angle;
public:
	OilView(const SdlTexture& tex, const int& angle);
 	virtual void drawAt(int x, int y) override;
 	virtual ~OilView() {}
};

#endif // OIL_VIEW_H