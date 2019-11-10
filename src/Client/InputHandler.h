#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include "SdlWindow.h"
#include "Audio.h"
#include "../Common/Event/Event.h"
#include "../Common/SafeQueue.h"

class InputHandler {
private:
	SdlWindow& window;
	Audio& audio;
	SafeQueue<Event*>& sendQueue;

	SDL_Event event;
	bool _done;
	bool fullscreen;
	bool up_pressed, left_pressed, down_pressed, right_pressed;
	int& clientId;
public:
	InputHandler(SdlWindow& window, Audio& audio,
		SafeQueue<Event*>& sendQueue, int& clientId);
	bool done();
	void handle();
};

#endif // INPUT_HANDLER_H
