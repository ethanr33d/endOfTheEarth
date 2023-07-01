// Abstract class that defines required functions for drawable objects

#pragma once

#include <SDL2/SDL.h>

class Drawable {
	protected:
		SDL_Renderer* m_renderer;
		bool m_shown;
		int m_x;
		int m_y;
		int m_w;
		int m_h;
	public:
		Drawable() : m_shown{ false }, m_x{ 0 }, m_y{ 0 }, m_w{ 0 }, m_h{ 0 } {};
		virtual void draw(SDL_Renderer* renderer) = 0;
		void show() { m_shown = true;  };
		void hide() { m_shown = false; };

		// default implementations provided for setPosition and set Size
		// derived classes can override if extra work needed
		virtual void setPosition(const int newX, const int newY) { m_x = newX; m_y = newY; };
		virtual void setSize(const int newW, const int newH) { m_w = newW, m_h = newH; };

		SDL_Rect getBounds() { return SDL_Rect{ m_x,m_y,m_w,m_h }; };
};
