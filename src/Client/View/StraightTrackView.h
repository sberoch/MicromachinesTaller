#ifndef STRAIGHT_TRACK_VIEW_H
#define STRAIGHT_TRACK_VIEW_H

#include "ObjectView.h"

class StraightTrackView : public ObjectView {
private:
	int angle;
public:
	StraightTrackView(const SdlTexture& tex, const int& angle);
 	virtual void drawAt(int x, int y) override;
 	virtual int getAngle() override;
 	virtual ~StraightTrackView() {}
};

#endif // STRAIGHT_TRACK_VIEW_H
