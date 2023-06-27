// Generic button class. Special case of a TextLabel able to respond to click and hover events

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cmath>
#include <functional>
#include "SDLUtils.h"
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

		bool hover;
		bool clicking;

		SDL_Color idleColor; // default color
		SDL_Color hoverColor;
		SDL_Color clickColor;

		std::function<void()> downHandler;
		std::function<void()> upHandler;
		std::function<void()> hoverStartHandler;
		std::function<void()> hoverEndHandler;
		
	public:
		Button(const std::string& text = "") : TextLabel(text), hover{false}, clicking{false},
			idleColor{DEFAULT_BG_COLOR}, hoverColor{ DEFAULT_HOVER_COLOR }, 
			clickColor{ DEFAULT_CLICK_COLOR }, downHandler{ nullptr }, upHandler{ nullptr }, 
			hoverStartHandler{ nullptr }, hoverEndHandler{ nullptr } {};

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
		virtual void draw(SDL_Renderer* renderer);
};