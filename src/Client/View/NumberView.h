#ifndef MICROMACHINES_NUMBERVIEW_H
#define MICROMACHINES_NUMBERVIEW_H

#include "ObjectView.h"

class NumberView : public ObjectView {
private:
	int _number;
public:
	NumberView(const SdlTexture& tex);
	void setNumber(int number);
	virtual void drawAt(int x, int y) override;
	virtual ~NumberView() = default;
};

#endif //MICROMACHINES_NUMBERVIEW_H
