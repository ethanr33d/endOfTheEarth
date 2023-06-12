// Interface that defines required functions for clickable objects

#pragma once

#include <SDL2/SDL.h>

class IClickable {
	public:
		virtual void mouseDown(SDL_MouseButtonEvent event) = 0;
		virtual void mouseUp(SDL_MouseButtonEvent event) = 0;
};
