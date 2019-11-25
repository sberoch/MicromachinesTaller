#ifndef CONVERTER_H
#define CONVERTER_H

class Converter {
private:
	int pixelesPerBlock;
public:
	explicit Converter(int pixelesPerBlock);
	int blockToPixel(float coord);
	float pixelToBlock(int coord);
};

#endif // CONVERTER_H
