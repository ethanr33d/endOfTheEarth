// Generic button class

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cmath>
#include <functional>
#include "SDLUtils.h"
#include "Drawable.h"
#include "IClickable.h"
#include "IHoverable.h"

class Button : public Drawable, public IClickable, public IHoverable {
	private:
		// Constants
		inline static const SDL_Color DEFAULT_BG_COLOR {180, 180, 180, 255};
		inline static const SDL_Color DEFAULT_BORDER_COLOR {0, 0, 0, 255};
		inline static const int DEFAULT_BORDER_SIZE = 2;
		inline static const char* FONT_RES_PATH = "fonts";
		inline static const std::string DEFAULT_FONT = SDLUtils::getResourceDirPath(FONT_RES_PATH) + "sansRegular.ttf";
		inline static const SDL_Color DEFAULT_FONT_COLOR {0, 0, 0, 255};
		inline static const int DEFAULT_FONT_SIZE = 60; // text is scaled from here to fit button width
		inline static const int TEXT_PADDING = 5;
		inline static const SDL_Color DEFAULT_HOVER_COLOR {128, 128, 128, 255};
		inline static const SDL_Color DEFAULT_CLICK_COLOR {200, 200, 200, 255};

		int x;
		int y;
		int w;
		int h;
		bool hover;
		bool clicking;

		SDL_Color borderColor;
		int borderSize;
		SDL_Color bgColor;
		TTF_Font* font;
		SDL_Color fontColor;
		SDL_Color hoverColor;
		SDL_Color clickColor;

		SDL_Texture* textTexture; // so texture does not have to be rendered every frame
		std::function<void()> downHandler;
		std::function<void()> upHandler;
		std::function<void()> hoverStartHandler;
		std::function<void()> hoverEndHandler;
		std::string buttonText;
		void createTextTexture(SDL_Renderer* renderer); // helper function for generating texture
		
	public:
		Button(std::string text = "") : x{ 0 }, y{ 0 }, w{ 0 }, h{ 0 }, hover{false}, 
			clicking{false}, borderColor{ DEFAULT_BORDER_COLOR }, 
			borderSize{ DEFAULT_BORDER_SIZE },bgColor{ DEFAULT_BG_COLOR }, 
			font{ nullptr }, fontColor{DEFAULT_FONT_COLOR}, hoverColor{ DEFAULT_HOVER_COLOR }, 
			clickColor{ DEFAULT_CLICK_COLOR }, textTexture {nullptr}, downHandler{ nullptr },
			upHandler{ nullptr }, hoverStartHandler{ nullptr }, hoverEndHandler{ nullptr }, 
			buttonText {text} {};

		~Button();
		void setPosition(int xPos, int yPos);
		void setSize(int width, int height);
		void setMouseDownHandle(std::function<void()> func);
		void setMouseUpHandle(std::function<void()> func);
		void setHoverStartHandle(std::function<void()> func);
		void setHoverEndHandle(std::function<void()> func);
		void setBorder(SDL_Color color, int size);

		// required functions
		virtual void mouseDown();
		virtual void mouseUp();
		virtual void mouseEnter();
		virtual void mouseLeave();

		virtual SDL_Rect getClickBox();
		virtual SDL_Rect getHoverBox();
		virtual void draw(SDL_Renderer* renderer);
};