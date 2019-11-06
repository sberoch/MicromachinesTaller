#include "ObjectView.h"
#include <iostream>

ObjectView::ObjectView(const SdlTexture& texture) : texture(texture) {}

void ObjectView::setInitialPos(int x, int y) {
	this->initialX = x; this->initialY = y;
}

void ObjectView::setState(int estado) {
	throw std::runtime_error("Setting state to wrong object type");
}

void ObjectView::move(int x, int y) {
	throw std::runtime_error("Moving wrong object type");
}

void ObjectView::resize(int newSize) {
	throw std::runtime_error("Resizing wrong object type");
}

void ObjectView::setRotation(int angulo) {
	throw std::runtime_error("Setting rotation to wrong object type");
}

void ObjectView::setId(int id) {
	this->id = id;
}

int ObjectView::getId() {
	return id;
}