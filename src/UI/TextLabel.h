// Generic text label class with background and border
#pragma once

#include <string>
#include "SDL2/SDL_ttf.h"
#include "../SDLUtils.h"
#include "UIFrame.h"
#include "TextNode.h"

class TextLabel : public UIFrame {
	protected:
		inline static const int TEXT_PADDING = 5;

		TextNode m_labelText;
	public:
		TextLabel(SDL_Renderer* renderer, const std::string& text = "");

		virtual void setSize(int x, int y) override; // need to recompute text scalar on setSize
		virtual void setPosition(int w, int h) override; // need to set position of text
		virtual void draw();

};