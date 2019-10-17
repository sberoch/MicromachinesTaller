#ifndef MUD_VIEW_H
#define MUD_VIEW_H

#include "ObjectView.h"

class MudView : public ObjectView {
private:
	int angle;
public:
	MudView(const SdlTexture& tex, const int& angle);
 	virtual void drawAt(int x, int y) override;
 	virtual ~MudView() {}
};

#endif // MUD_VIEW_H