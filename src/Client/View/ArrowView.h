#ifndef ARROW_VIEW_H
#define ARROW_VIEW_H

#include "ObjectView.h"

class ArrowView : public ObjectView {
public:
	ArrowView(const SdlTexture& tex);
 	virtual void drawAt(int x, int y) override;
 	virtual ~ArrowView() {}
};

#endif // ARROW_VIEW_H
