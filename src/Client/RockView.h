#ifndef ROCK_VIEW
#define ROCK_VIEW

#include "ObjectView.h"

class RockView : public ObjectView {
public:
	RockView(const SdlTexture& tex);
 	virtual void drawAt(int x, int y) override;
 	virtual ~RockView() {}
};

#endif // ROCK_VIEW