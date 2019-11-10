#ifndef ROOM_VIEW_H
#define ROOM_VIEW_H

#include "ObjectView.h"

class RoomView : public ObjectView {
public:
	RoomView(const SdlTexture& tex);
	virtual void drawAt(int x, int y) override;
 	virtual ~RoomView() {}
};

#endif // ROOM_VIEW_H
