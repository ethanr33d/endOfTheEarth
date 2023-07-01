// Abstract class that defines required functions for drawable objects

#pragma once

#include <SDL2/SDL.h>

class Drawable {
	protected:
		SDL_Renderer* m_renderer;
		bool m_shown;
		SDL_Rect m_bounds;

	public:
		Drawable(SDL_Renderer* renderer) : m_renderer{ renderer },
			m_shown{ false }, m_bounds{ 0,0,0,0 } {};

		virtual void draw() = 0;
		void show() { m_shown = true;  };
		void hide() { m_shown = false; };

		// default implementations provided for setPosition and set Size
		// derived classes can override if extra work needed
		virtual void setPosition(const int newX, const int newY) { m_bounds.x = newX; m_bounds.y = newY; };
		virtual void setSize(const int newW, const int newH) { m_bounds.w = newW, m_bounds.h = newH; };

		SDL_Rect getBounds() { return m_bounds; };
};
