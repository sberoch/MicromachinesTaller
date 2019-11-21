#ifndef MICROMACHINES_LAPSTEXTVIEW_H
#define MICROMACHINES_LAPSTEXTVIEW_H

#include "ObjectView.h"

class LapsTextView : public ObjectView {
public:
public:
	explicit LapsTextView(const SdlTexture& tex);
	virtual void drawAt(int x, int y) override;
	virtual ~LapsTextView() = default;
};

#endif //MICROMACHINES_LAPSTEXTVIEW_H
