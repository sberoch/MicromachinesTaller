#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include "SdlWindow.h"
#include "Audio.h"
#include "../Common/Event/Event.h"
#include "../Common/SafeQueue.h"
#include "PlayerDescriptor.h"
#include "ScreenRecorder.h"

class InputHandler {
private:
	SdlWindow& window;
	Audio& audio;
	ScreenRecorder& recorder;
	SafeQueue<std::shared_ptr<Event>>& sendQueue;

	SDL_Event event;
	bool _done;
	bool fullscreen;
	bool up_pressed, left_pressed, down_pressed, right_pressed;
	PlayerDescriptor& player;
public:
	InputHandler(SdlWindow& window, Audio& audio, ScreenRecorder& recorder,
				 SafeQueue<std::shared_ptr<Event>>& sendQueue, PlayerDescriptor& player);
	bool done();
	void handle();
};

#endif // INPUT_HANDLER_H
