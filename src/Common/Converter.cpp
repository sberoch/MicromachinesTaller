#include "Converter.h"
#include <cmath>

Converter::Converter(int pixelesPerBlock) : 
	pixelesPerBlock(pixelesPerBlock) {}

int Converter::blockToPixel(float coord) {
	return round((pixelesPerBlock*coord) + pixelesPerBlock/2);
}

float Converter::pixelToBlock(int coord) {
	return ((float) (coord - pixelesPerBlock/2) / pixelesPerBlock);
}