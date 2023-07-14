// Basic physics enabled rectangle

#pragma once

#include "PhysicsElement.h"

class Brick : public PhysicsElement {
	private:
	SDL_Color m_color;

	public:
		Brick(SDL_Renderer* renderer) : PhysicsElement(renderer), m_color(SDL_Color{ 0,0,0, 255 }) {};

		void setColor(const SDL_Color& color);
		virtual void draw();
};