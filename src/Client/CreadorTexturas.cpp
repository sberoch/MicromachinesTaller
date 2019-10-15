#include "CreadorTexturas.h"
#include <iostream>
#include "../Common/Constantes.h"

#include "VistaPistaRecta.h"
#include "VistaPistaCurva.h"

CreadorTexturas::CreadorTexturas(const SdlWindow& window) :
	pistaRectaTex("pista_recta.png", window),
	pistaCurvaTex("pista_curva.png", window) {
		contadorID = 0;
}

VistaObjetoPtr CreadorTexturas::crear(int tipo, int x, int y, int angulo) {
	VistaObjetoPtr vo;
	switch (tipo) {
		case ID_PISTA_RECTA: vo.reset(new VistaPistaRecta(pistaRectaTex, angulo)); break;
		case ID_PISTA_CURVA: vo.reset(new VistaPistaCurva(pistaCurvaTex, angulo)); break;
		default: throw std::runtime_error("Error obteniendo vista del objeto debido a id incorrecto");
	}
	++contadorID;
	vo->setPosInicial(x, y);
	vo->setId(contadorID);
	return vo;
}