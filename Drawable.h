// Abstract class that defines required functions for drawable objects

#pragma once

#include <SDL2/SDL.h>

class Drawable {
	protected:
		bool shown;
	public:
		Drawable() : shown{ false } {};
		virtual void draw(SDL_Renderer* renderer) = 0;
		void show() { shown = true;  };
		void hide() { shown = false; };
};
