// Interface that defines required functions for clickable objects

#pragma once

#include <SDL2/SDL.h>

class IClickable {
	public:
		virtual void mouseDown() = 0;
		virtual void mouseUp() = 0;
};
