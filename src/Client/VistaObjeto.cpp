#include "VistaObjeto.h"
#include <iostream>

void VistaObjeto::setPosInicial(int x, int y) {
	this->xInicial = x; this->yInicial = y;
}

void VistaObjeto::asignarEstado(int estado) {
	throw std::runtime_error("Asignando estado a objeto incorrecto");
}

void VistaObjeto::mover(int x, int y) {
	throw std::runtime_error("Intentando mover objeto incorrecto");
}

void VistaObjeto::flip(int flip) {
	throw std::runtime_error("Intentando flipear objeto incorrecto");
}

void VistaObjeto::asignarRotacion(int angulo) {
	throw std::runtime_error("Intentando rotar objeto incorrecto");
}

void VistaObjeto::setId(int id) {
	this->id = id;
}

int VistaObjeto::getId() {
	return id;
}