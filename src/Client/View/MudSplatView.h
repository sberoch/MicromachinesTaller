#ifndef MUD_SPLAT_VIEW_H
#define MUD_SPLAT_VIEW_H

#include "ObjectView.h"

class MudSplatView : public ObjectView {
public:
	MudSplatView(const SdlTexture& tex);
	void setDims(int x, int y);
	virtual void drawAt(int x, int y) override;
 	virtual ~MudSplatView() {}
};

#endif // MUD_SPLAT_VIEW_H
