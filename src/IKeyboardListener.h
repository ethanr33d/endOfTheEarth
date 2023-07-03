// interface for elements that listen to keyboard input
#pragma once

#include <SDL2/SDL.h>

class IKeyboardListener {
	public:
		virtual void keyDown(SDL_Keycode key) = 0;
		virtual void keyUp(SDL_Keycode key) = 0;
};