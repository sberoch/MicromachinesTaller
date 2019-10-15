#ifndef CREADOR_TEXTURAS
#define CREADOR_TEXTURAS 

#include "SdlWindow.h"
#include <memory>
#include "SdlTexture.h"
#include "VistaObjeto.h"

typedef std::shared_ptr<VistaObjeto> VistaObjetoPtr;

class CreadorTexturas {
private:
	//Id que se le asigna a cada objeto creado para luego hacerle referencia
	int contadorID;

	//Texturas
	SdlTexture pistaRectaTex;
	SdlTexture pistaCurvaTex;
public:
	CreadorTexturas(const SdlWindow& window);
	VistaObjetoPtr crear(int tipo, int x, int y, int angulo);
};

#endif