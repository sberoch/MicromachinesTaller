#ifndef TEXTURE_CREATOR
#define TEXTURE_CREATOR 

#include "SdlWindow.h"
#include <memory>
#include "SdlTexture.h"
#include "View/ObjectView.h"

typedef std::shared_ptr<ObjectView> ObjectViewPtr;

class TextureCreator {
private:
	//Textures
	SdlTexture straightTrackTex;
	SdlTexture curveTrackTex;
	SdlTexture powerupTex;
	SdlTexture rockTex;
	SdlTexture carRedTex;
	SdlTexture carBlueTex;
	SdlTexture carYellowTex;
	SdlTexture carGreenTex;
	SdlTexture oilTex;
	SdlTexture mudTex;
	SdlTexture explosionTex;
	SdlTexture mudSplatTex;
	SdlTexture startLineTex;
public:
	TextureCreator(const SdlWindow& window);
	ObjectViewPtr create(int type, int x, int y, int angle);
};

#endif