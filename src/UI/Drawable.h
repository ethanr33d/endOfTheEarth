// Abstract class that defines required functions for drawable objects

#pragma once

#include <SDL2/SDL.h>

class Drawable {
	protected:
		bool shown;
		int x;
		int y;
		int w;
		int h;
	public:
		Drawable() : shown{ false }, x{ 0 }, y{ 0 }, w{ 0 }, h{ 0 } {};
		virtual void draw(SDL_Renderer* renderer) = 0;
		void show() { shown = true;  };
		void hide() { shown = false; };
		void setPosition(const int newX, const int newY) { x = newX; y = newY; };
		void setSize(const int newW, const int newH) { w = newW, h = newH; };

		SDL_Rect getBounds() { return SDL_Rect{ x,y,w,h }; };
};
