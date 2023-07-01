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
		inline static const int DEFAULT_FONT_SIZE = 60;
		inline static const int DEFAULT_WRAP_ALIGN = TTF_WRAPPED_ALIGN_CENTER;

		std::string m_nodeText;
		SDL_Texture* m_textTexture;
		TTF_Font* m_font;
		SDL_Rect m_textBounds; // bounds of text texture
		bool m_customBoundsSet; // if bounds are set by setSize text texture is scaled to fit m_bounds rect

		int m_fontSize;
		SDL_Color m_fontColor;
		bool m_wrapped;

		// helper function for generating/regenerating texture. Properly frees memory
		void createTextTexture();
	public:
		~TextNode();
		
		// creators should use constructor if they plan to change defaults since calls to
		// manipulators require texture regeneration
		TextNode(SDL_Renderer* renderer, const std::string& text,
			const int size = DEFAULT_FONT_SIZE, const bool wrapped = false, 
			const std::string & fontFile = DEFAULT_FONT);

		// these functions require texture to be regenerated after calling,
		// prefer constructor if not changing these dynamically
		void setFontColor(const SDL_Color& color);
		void setText(const std::string& text);
		void setFontSize(const int size);
		void setFont(const std::string& font, int fontSize);
		void setWrapped(const bool wrap);
		
		SDL_Rect getTextBounds(); // return bounds of text texture
		virtual void setSize(int w, int h) override;
		virtual void draw();
};