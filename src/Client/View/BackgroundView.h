#ifndef BACKGROUND_VIEW_H
#define BACKGROUND_VIEW_H

#include "ObjectView.h"

class BackgroundView : public ObjectView {
public:
	BackgroundView(const SdlTexture& tex);
	void setDims(int x, int y);
 	virtual void drawAt(int x, int y) override;
 	virtual ~BackgroundView() {}
};

#endif // BACKGROUND_VIEW_H
