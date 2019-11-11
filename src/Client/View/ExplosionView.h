#ifndef EXPLOSION_VIEW_H
#define EXPLOSION_VIEW_H

#include "ObjectView.h"

class ExplosionView : public ObjectView {
private:
	int frame;
	int totalFrames;
	bool done;
public:
	ExplosionView(const SdlTexture& tex);
 	virtual void drawAt(int x, int y) override;
 	virtual ~ExplosionView() {}
};

#endif // EXPLOSION_VIEW_H
