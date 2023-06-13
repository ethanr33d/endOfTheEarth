// Generic button class

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cmath>
#include "SDLUtils.h"
#include "Renderable.h"
#include "IClickable.h"
class Button : public Renderable, public IClickable {
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
		int x;
		int y;
		int w;
		int h;
		SDL_Color borderColor;
		int borderSize;
		SDL_Color bgColor;
		TTF_Font* font;
		SDL_Color fontColor;
		SDL_Texture* textTexture; // so texture does not have to be rendered every frame
		void (*downHandler) ();
		void (*upHandler) ();
		std::string buttonText;
		void createTextTexture(SDL_Renderer* renderer); // helper function for generating texture
	public:
		Button(std::string buttonText = "") : x{ 0 }, y{ 0 }, w{ 0 }, h{ 0 },
			borderColor{ DEFAULT_BORDER_COLOR }, borderSize{ DEFAULT_BORDER_SIZE },
			bgColor{ DEFAULT_BG_COLOR }, font{ TTF_OpenFont(DEFAULT_FONT.c_str(), DEFAULT_FONT_SIZE)},
			fontColor{ DEFAULT_FONT_COLOR }, textTexture{ nullptr }, downHandler{ nullptr },
			upHandler{ nullptr }, buttonText{ buttonText } {};

		~Button();
		void setPosition(int xPos, int yPos);
		void setSize(int width, int height);
		void setMouseDownHandle(void (*func) ());
		void setMouseUpHandle(void (*func) ());
		void setBorder(SDL_Color color, int size);
		virtual void mouseDown();
		virtual void mouseUp();
		virtual void render(SDL_Renderer* renderer);
};