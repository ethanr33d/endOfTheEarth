#pragma once

#include <vector>
#include "../Drawable.h"

class PhysicsEngine {
	private:
	std::vector<Drawable*> m_collidableElements;

	std::vector<SDL_Rect> getCollisions(const SDL_Rect& queryRect, const Drawable* ignoreElement = nullptr);

	public:
		// return the nearest valid coordinates to desiredBounds such that there are no collisions 
		// between any objects. 
		// NOTE: Assumes that currentBounds are valid. 
		SDL_Rect getNearestValidCoords(const Drawable* element, const int destX, const int destY);
		void addCollidableElement(Drawable* element);
};

