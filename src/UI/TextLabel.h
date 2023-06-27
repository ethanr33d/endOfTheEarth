// Generic text label class with background and border
#pragma once

#include <string>
#include "SDL2/SDL_ttf.h"
#include "SDLUtils.h"
#include "UIFrame.h"
#include "TextNode.h"

class TextLabel : public UIFrame {
	protected:
		inline static const int TEXT_PADDING = 5;

		TextNode labelText;
	public:
		TextLabel(const std::string& text = "") : labelText{ TextNode(text) } { labelText.show(); };

		virtual void draw(SDL_Renderer* renderer);

};