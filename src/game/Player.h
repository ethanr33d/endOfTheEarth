#pragma once

#include "SDL2/SDL.h"
#include "../Drawable.h"

class Player : public Drawable {
	public:
		Player(SDL_Renderer* renderer) : Drawable(renderer) {};
		virtual void draw();
};