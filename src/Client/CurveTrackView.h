#ifndef VISTA_CURVA_RECTA_H
#define VISTA_CURVA_RECTA_H

#include "ObjectView.h"

class CurveTrackView : public ObjectView {
private:
	int angle;
public:
	CurveTrackView(const SdlTexture& tex, const int& angle);
 	virtual void drawAt(int x, int y) override;
 	virtual ~CurveTrackView() {}
};

#endif // VISTA_CURVA_RECTA_H