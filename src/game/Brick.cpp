#include "Brick.h"

void Brick::setColor(const SDL_Color& color) {
	m_color = color;
}

void Brick::draw() {
	SDL_Rect intBounds = getRenderBounds();

	SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRect(m_renderer, &intBounds);
}