#ifndef VISTA_OBJETO
#define VISTA_OBJETO

#include "Area.h"
#include "SdlTexture.h"
#include <vector>

class VistaObjeto {
protected:
	int id;
	SdlTexture textura;
	std::vector<Area> clips;
	int xInicial, yInicial;
	int frame;
	int tamanioHorizontal;
	int tamanioVertical;
public:
	virtual void dibujarEn(int x, int y) = 0;
	virtual void asignarEstado(int estado);
	virtual void mover(int x, int y);
	virtual void asignarRotacion(int angulo);
	virtual void flip(int flip);
	void setPosInicial(int x, int y);
	void setId(int id);
	int getId();
	virtual ~VistaObjeto() {}
};

#endif