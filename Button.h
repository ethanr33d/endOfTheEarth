// Generic button class

#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "Renderable.h"
#include "IClickable.h"
class Button : Renderable, IClickable {
	private:
		// Constants
		inline static const SDL_Color DEFAULT_BG_COLOR {180, 180, 180};
		inline static const SDL_Color DEFAULT_BORDER_COLOR {0, 0, 0};
		inline static const int DEFAULT_BORDER_SIZE = 2;
		
		int xPos;
		int yPos;
		SDL_Color borderColor;
		int borderSize;
		SDL_Color bgColor;
		void* handler;
		std::string buttonText;
	public:
		Button(std::string buttonText = ""): xPos{0}, yPos{0}, borderColor{DEFAULT_BORDER_COLOR}, 
			borderSize{DEFAULT_BORDER_SIZE}, bgColor{DEFAULT_BG_COLOR}, handler {nullptr},
			buttonText{buttonText} {};

		void SetPosition(int x, int y);
		void OnClick(void* func);
		void SetBorder(SDL_Color color, int size);
};