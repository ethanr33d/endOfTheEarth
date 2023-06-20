// Interface that defines required functions for clickable objects

#pragma once

#include <SDL2/SDL.h>

class IClickable {
	public:

		// will be called when respective events are detected on object by engine
		virtual void mouseDown() = 0;
		virtual void mouseUp() = 0;

		// returns the x,y,w,h of clickable area so the engine can properly look for events
		virtual SDL_Rect getClickBox() = 0;
};
