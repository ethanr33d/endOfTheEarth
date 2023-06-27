// Class that defines required methods for hoverable objects
#pragma once

#include "SDL2/SDL.h"

class IHoverable {
	private:

	public:
		// will be called when respective events are detected by engine for object
		virtual void mouseEnter() = 0;
		virtual void mouseLeave() = 0;

		// returns the x,y,w,h of hoverable area so the engine can properly look for events
		virtual SDL_Rect getHoverBox() = 0;
};