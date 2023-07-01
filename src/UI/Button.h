// Generic button class. Special case of a TextLabel able to respond to click and hover events

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cmath>
#include <functional>
#include "../SDLUtils.h"
#include "TextLabel.h"
#include "IClickable.h"
#include "IHoverable.h"

class Button : public TextLabel, public IClickable, public IHoverable {
	private:
		/* Constants */

		// Override of TextLabel
		inline static const SDL_Color DEFAULT_BG_COLOR {180, 180, 180, 255};

		inline static const SDL_Color DEFAULT_HOVER_COLOR {128, 128, 128, 255};
		inline static const SDL_Color DEFAULT_CLICK_COLOR {200, 200, 200, 255};

		bool m_hover;
		bool m_clicking;

		SDL_Color m_idleColor; // default color
		SDL_Color m_hoverColor;
		SDL_Color m_clickColor;

		std::function<void()> m_downHandler;
		std::function<void()> m_upHandler;
		std::function<void()> m_hoverStartHandler;
		std::function<void()> m_hoverEndHandler;
		
	public:
		Button(SDL_Renderer* renderer, const std::string& text = "") : TextLabel(renderer, text), 
			m_hover{false}, m_clicking{false}, m_idleColor{DEFAULT_BG_COLOR},
			m_hoverColor{ DEFAULT_HOVER_COLOR }, m_clickColor{ DEFAULT_CLICK_COLOR }, 
			m_downHandler{ nullptr }, m_upHandler{ nullptr }, m_hoverStartHandler{ nullptr },
			m_hoverEndHandler{ nullptr } {};

		void setMouseDownHandle(const std::function<void()>& func);
		void setMouseUpHandle(const std::function<void()>& func);
		void setHoverStartHandle(const std::function<void()>& func);
		void setHoverEndHandle(const std::function<void()>& func);

		// required functions
		virtual void mouseDown();
		virtual void mouseUp();
		virtual void mouseEnter();
		virtual void mouseLeave();

		virtual SDL_Rect getClickBox();
		virtual SDL_Rect getHoverBox();
		virtual void draw();
};