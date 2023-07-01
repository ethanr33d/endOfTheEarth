#include "Player.h"

void Player::draw() {
	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(m_renderer, &m_bounds);
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
}