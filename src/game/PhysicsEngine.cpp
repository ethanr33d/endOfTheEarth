#include "PhysicsEngine.h"
#include <iostream>

std::vector<SDL_Rect> PhysicsEngine::getCollisions(const SDL_Rect& queryRect, const Drawable* ignoreElement) {
	std::vector<SDL_Rect> collidingElements;

	for (Drawable* element : m_collidableElements) {
		if (element == ignoreElement) continue;

		SDL_Rect eleBounds = element->getBounds();

		// if colliding on both x and y axis then they are truely colliding
		if (queryRect.x < eleBounds.x + eleBounds.w && queryRect.x + queryRect.w > eleBounds.x
				&& queryRect.y < eleBounds.y + eleBounds.h  && queryRect.y + queryRect.h > eleBounds.y) {

			collidingElements.push_back(eleBounds);
		}
	}

	return collidingElements;
}

SDL_Rect PhysicsEngine::getNearestValidCoords(const Drawable* element, const int destX, const int destY) {
	SDL_Rect currentBox = element->getBounds();
	SDL_Rect destBox = currentBox; // default back to original position if no possible movement

	// if no change desired on axis skip checking
	if (destX != currentBox.x) {
		// create a query rectangle between currentPos and destPos to find elements blocking path
		SDL_Rect queryRect{ currentBox.x + currentBox.w, currentBox.y,
			abs(destX - currentBox.x), currentBox.h };

		if (destX < currentBox.x) {
			queryRect.x = destX;
		}

		std::vector<SDL_Rect> collisions = getCollisions(queryRect, element);

		if (collisions.size() == 0) { // no collisions, safe to move
			destBox.x = destX;
		}
		else {
			SDL_Rect smallestBox{ INT_MAX, 0, 0, 0 };

			// find the nearest collision to currentPos
			for (SDL_Rect box : collisions) {
				if (abs(box.x - currentBox.x) < smallestBox.x) {
					smallestBox = box;
				}
			}

			// back destRect up so it doesn't collide with smallestBox
			destBox.x = currentBox.x < smallestBox.x ? smallestBox.x - currentBox.h : smallestBox.x + smallestBox.w;
		}
	}

	if (destY != currentBox.y) {
		// create a query rectangle between currentPos and destPos to find elements blocking path
		// using destRect for x since x position may have changed from above
		SDL_Rect queryRect{ destBox.x, currentBox.y + currentBox.h, 
			currentBox.w, abs(destY - currentBox.y)};

		if (destY < currentBox.y) {
			queryRect.y = destY;
		}
		std::vector<SDL_Rect> collisions = getCollisions(queryRect, element);

		if (collisions.size() == 0) { // no collisions, safe to move
			destBox.y = destY;
		}
		else {
			SDL_Rect smallestBox{ 0, INT_MAX, 0, 0 };

			// find the nearest collision to currentPos
			for (SDL_Rect box : collisions) {
				if (abs(box.y - currentBox.y) < smallestBox.y) {
					smallestBox = box;
				}
				
			}

			destBox.y = currentBox.y < smallestBox.y ? smallestBox.y - currentBox.h : smallestBox.y + smallestBox.h;
		}
	}

	return destBox;
}

void PhysicsEngine::addCollidableElement(Drawable* element) {
	m_collidableElements.push_back(element);
}