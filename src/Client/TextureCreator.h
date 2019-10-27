#ifndef TEXTURE_CREATOR
#define TEXTURE_CREATOR 

#include "SdlWindow.h"
#include <memory>
#include "SdlTexture.h"
#include "View/ObjectView.h"

typedef std::shared_ptr<ObjectView> ObjectViewPtr;

class TextureCreator {
private:
	//Assigned to each view to later reference them.
	int idCounter;

	//Textures
	SdlTexture straightTrackTex;
	SdlTexture curveTrackTex;
	SdlTexture powerupTex;
	SdlTexture rockTex;
	SdlTexture car1Tex;
	SdlTexture car2Tex;
	SdlTexture car3Tex;
	SdlTexture car4Tex;
	SdlTexture oilTex;
	SdlTexture mudTex;
public:
	TextureCreator(const SdlWindow& window);
	ObjectViewPtr create(int type, int x, int y, int angle);
};

#endif