#ifndef TEXTURE_CREATOR
#define TEXTURE_CREATOR 

#include "SdlWindow.h"
#include <memory>
#include "SdlTexture.h"
#include "ObjectView.h"

typedef std::shared_ptr<ObjectView> ObjectViewPtr;

class TextureCreator {
private:
	//Assigned to each view to later reference them.
	int idCounter;

	//Textures
	SdlTexture straightTrackTex;
	SdlTexture curveTrackTex;
	SdlTexture powerupTex;
public:
	TextureCreator(const SdlWindow& window);
	ObjectViewPtr create(int type, int x, int y, int angle);
};

#endif