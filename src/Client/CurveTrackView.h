#ifndef CURVE_TRACK_VIEW
#define CURVE_TRACK_VIEW

#include "ObjectView.h"

class CurveTrackView : public ObjectView {
private:
	int angle;
public:
	CurveTrackView(const SdlTexture& tex, const int& angle);
 	virtual void drawAt(int x, int y) override;
 	virtual ~CurveTrackView() {}
};

#endif // CURVE_TRACK_VIEW