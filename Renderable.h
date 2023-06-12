// Abstract class that defines required functions for renderable objects

#pragma once

#include <SDL2/SDL.h>

class Renderable {
	protected:
		bool shown;
	public:
		Renderable() : shown{ false } {};
		virtual void render(SDL_Renderer* renderer) = 0;
		void show() { shown = true;  };
		void hide() { shown = false; };
};
