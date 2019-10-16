#ifndef CONVERTER_H
#define CONVERTER_H

class Converter {
private:
	int pixelesPerBlock;
public:
	Converter(int pixelesPerBlock);
	int blockToPixel(float coord);
	float pixelToBlock(int coord);
};

#endif // CONVERTER_H
