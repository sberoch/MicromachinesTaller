#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include "SdlWindow.h"

class InputHandler {
private:
	SdlWindow& window;

	SDL_Event event;
	bool terminado;
	bool fullscreen;
public:
	InputHandler(SdlWindow& window);
	bool termino();
	void handle();
};

#endif // INPUT_HANDLER_H
