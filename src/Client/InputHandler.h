#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include "SdlWindow.h"

class InputHandler {
private:
	SdlWindow& window;

	SDL_Event event;
	bool _done;
	bool fullscreen;
public:
	InputHandler(SdlWindow& window);
	bool done();
	void handle();
};

#endif // INPUT_HANDLER_H
