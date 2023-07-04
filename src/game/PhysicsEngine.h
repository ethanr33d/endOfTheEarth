#pragma once

#include <vector>
#include "../Drawable.h"

class PhysicsEngine {
	private:
	std::vector<Drawable*> collidableElements;

	std::vector<SDL_Rect> getXAxisCollisions(const SDL_Rect& queryRect);

	public:
		// return the nearest valid coordinates to desiredBounds such that there are no collisions 
		// between any objects. 
		// NOTE: Assumes that currentBounds are valid. 
		SDL_Rect getNearestValidCoords(const SDL_Rect& currentBounds, const int destX, const int destY);
};
