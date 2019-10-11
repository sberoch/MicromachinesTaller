#include "Area.h"
#include <iostream>

Area::Area() {
	x = 0; y = 0; width = 0; height = 0;
}

void Area::set(int x, int y, int width, int height) {
	this->x = x; this->y = y;
	this->width = width; this->height = height;
}

Area::Area(int x, int y, int width, int height) :
	x(x), y(y), width(width), height(height){
}
	
int Area::getX() const {
	return this->x;
}
int Area::getY() const {
	return this->y;
}
int Area::getWidth() const {
	return this->width;
}
int Area::getHeight() const {
	return this->height;
}

bool Area::estaAdentro(int x, int y) {
	if (this->x > x || x > (this->x + this->width)) return false;
    if (this->y > y || y > (this->y + this->height)) return false;
	return true;
}