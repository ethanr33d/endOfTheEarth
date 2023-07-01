#include "UIFrame.h"

void UIFrame::setBorderColor(const SDL_Color& color) {
	m_borderColor = color;
}

void UIFrame::setBorderSize(const int size) {
	m_borderSize = size;
}

void UIFrame::setBGColor(const SDL_Color& color) {
	m_bgColor = color;
}

void UIFrame::draw(SDL_Renderer* renderer) {
	if (!m_shown) return;
	
	//border not included in width and height
	SDL_Rect borderRect{ 
		m_x - m_borderSize,
		m_y - m_borderSize,
		m_w + 2 * m_borderSize,
		m_h + 2 * m_borderSize
	};

	SDL_Rect bgRect{ m_x, m_y, m_w, m_h };

	SDL_SetRenderDrawColor(renderer, m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a);
	SDL_RenderFillRect(renderer, &borderRect);

	SDL_SetRenderDrawColor(renderer, m_bgColor.r, m_bgColor.g, m_bgColor.b, m_bgColor.a);
	SDL_RenderFillRect(renderer, &bgRect);
}
