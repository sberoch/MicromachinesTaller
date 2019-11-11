#include "ObjectView.h"
#include <iostream>

ObjectView::ObjectView(const SdlTexture& texture) : texture(texture) {}

void ObjectView::setInitialPos(int x, int y) {
	this->initialX = x; this->initialY = y;
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

int ObjectView::getAngle() {
	throw std::runtime_error("Trying to get angle of wrong object type");
	return 0;
}

int ObjectView::getX() {
	return initialX;
}

int ObjectView::getY() {
	return initialY;
}