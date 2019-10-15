#ifndef VISTA_CURVA_RECTA_H
#define VISTA_CURVA_RECTA_H

#include "VistaObjeto.h"

class VistaPistaCurva : public VistaObjeto {
private:
	int angulo;
public:
	VistaPistaCurva(const SdlTexture& tex, const int& angulo);
 	virtual void dibujarEn(int x, int y) override;
 	virtual ~VistaPistaCurva() {}
};

#endif // VISTA_CURVA_RECTA_H