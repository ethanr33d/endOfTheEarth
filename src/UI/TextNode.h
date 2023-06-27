// Wrapper for a text texture with easier access to attributes and text manipulation

#pragma once

#include <string>
#include "Drawable.h"
#include "../SDLUtils.h"

class TextNode : public Drawable {
	private:
		inline static const char* FONT_RES_PATH = "fonts";
		inline static const std::string DEFAULT_FONT = SDLUtils::getResourceDirPath(FONT_RES_PATH) + "sansRegular.ttf";
		inline static const SDL_Color DEFAULT_FONT_COLOR {0, 0, 0, 255};
		inline static const int DEFAULT_FONT_SIZE = 60; // text is scaled from here to fit button width

		std::string nodeText;
		SDL_Texture* textTexture;
		TTF_Font* font;
		int fontSize;
		SDL_Color fontColor;
		void createTextTexture(SDL_Renderer* renderer); // helper function for generating texture
	public:
		~TextNode();
		TextNode(const std::string& text, const std::string& fontFile = DEFAULT_FONT,
			const int size = DEFAULT_FONT_SIZE);

		void setFontColor(const SDL_Color& color);
		void setFontSize(const int size);
		void setText(const std::string& text);
		void setFont(const std::string& font, int fontSize);
		
		virtual void draw(SDL_Renderer* renderer);
};