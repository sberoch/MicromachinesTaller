#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include "SdlWindow.h"
#include "Audio.h"
#include "../Common/Queue.h"
#include "../Common/BlockingQueue.h"
#include <string>

class InputHandler {
private:
	SdlWindow& window;
	Audio& audio;
	BlockingQueue& sendQueue;

	SDL_Event event;
	bool _done;
	bool fullscreen;
public:
	InputHandler(SdlWindow& window, Audio& audio,
		BlockingQueue& sendQueue);
	bool done();
	void handle();
};

#endif // INPUT_HANDLER_H
