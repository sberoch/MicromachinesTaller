#ifndef VISTA_PISTA_RECTA_H
#define VISTA_PISTA_RECTA_H

#include "VistaObjeto.h"

class VistaPistaRecta : public VistaObjeto {
private:
	int angulo;
public:
	VistaPistaRecta(const SdlTexture& tex, const int& angulo);
 	virtual void dibujarEn(int x, int y) override;
 	virtual ~VistaPistaRecta() {}
};

#endif // VISTA_PISTA_RECTA_H
