// Generic UIFrame with color background and border
#pragma once

#include "Drawable.h"

class UIFrame : public Drawable {
	private:
	protected:
		inline static const SDL_Color DEFAULT_BG_COLOR {255, 255, 255, 255};
		inline static const SDL_Color DEFAULT_BORDER_COLOR {0, 0, 0, 255};
		inline static const int DEFAULT_BORDER_SIZE = 2;

		SDL_Color m_borderColor;
		int m_borderSize;
		SDL_Color m_bgColor;
		
		void setBorderColor(const SDL_Color& color);
		void setBorderSize(const int size);
		void setBGColor(const SDL_Color& color);
	public:
		UIFrame(SDL_Renderer* renderer) : Drawable(renderer), m_borderColor{ DEFAULT_BORDER_COLOR },
			m_borderSize{ DEFAULT_BORDER_SIZE }, m_bgColor{ DEFAULT_BG_COLOR } {};

		virtual void draw();
};