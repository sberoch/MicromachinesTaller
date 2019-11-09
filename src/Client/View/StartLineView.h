#ifndef START_LINE_VIEW_H
#define START_LINE_VIEW_H

#include "ObjectView.h"

class StartLineView : public ObjectView {
private:
	int angle;
public:
	StartLineView(const SdlTexture& tex, const int& angle);
 	virtual void drawAt(int x, int y) override;
 	virtual int getAngle() override;
 	virtual ~StartLineView() {}
};

#endif // START_LINE_VIEW_H
