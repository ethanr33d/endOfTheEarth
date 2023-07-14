#include "PhysicsEngine.h"
#include <iostream>

std::vector<PhysicsRect> PhysicsEngine::getCollisions(const PhysicsRect& queryRect, const PhysicsElement* ignoreElement) {
	std::vector<PhysicsRect> collidingElements;

	for (PhysicsElement* element : m_collidableElements) {
		if (element == ignoreElement) continue;

		PhysicsRect eleBounds = element->getBounds();

		// if colliding on both x and y axis then they are truely colliding
		if (queryRect.x < eleBounds.x + eleBounds.w && queryRect.x + queryRect.w > eleBounds.x
				&& queryRect.y < eleBounds.y + eleBounds.h  && queryRect.y + queryRect.h > eleBounds.y) {

			collidingElements.push_back(eleBounds);
		}
	}

	return collidingElements;
}

Vector2 PhysicsEngine::getNearestValidCoords(const PhysicsElement* element, const double destX, const double destY) {
	PhysicsRect currentBox = element->getBounds();
	PhysicsRect destBox = currentBox; // default back to original position if no possible movement

	// if no change desired on axis skip checking
	if (destX != currentBox.x) {
		// create a query rectangle between currentPos and destPos to find elements blocking path
		PhysicsRect queryRect{ currentBox.x + currentBox.w, currentBox.y,
			abs(destX - currentBox.x), currentBox.h };

		if (destX < currentBox.x) {
			queryRect.x = destX;
		}

		std::vector<PhysicsRect> collisions = getCollisions(queryRect, element);

		if (collisions.size() == 0) { // no collisions, safe to move
			destBox.x = destX;
		}
		else {
			PhysicsRect smallestBox{ INT_MAX, 0, 0, 0 };

			// find the nearest collision to currentPos
			for (const PhysicsRect& box : collisions) {
				if (abs(box.x - currentBox.x) < smallestBox.x) {
					smallestBox = box;
				}
			}

			// back destRect up so it doesn't collide with smallestBox
			destBox.x = currentBox.x < smallestBox.x ? smallestBox.x - currentBox.w : smallestBox.x + smallestBox.w;
		}
	}

	if (destY != currentBox.y) {
		// create a query rectangle between currentPos and destPos to find elements blocking path
		// using destRect for x since x position may have changed from above
		PhysicsRect queryRect{ destBox.x, currentBox.y + currentBox.h, 
			currentBox.w, abs(destY - currentBox.y)};

		if (destY < currentBox.y) {
			queryRect.y = destY;
		}
		std::vector<PhysicsRect> collisions = getCollisions(queryRect, element);

		if (collisions.size() == 0) { // no collisions, safe to move
			destBox.y = destY;
		}
		else {
			PhysicsRect smallestBox{ 0, INT_MAX, 0, 0 };

			// find the nearest collision to currentPos
			for (const PhysicsRect& box : collisions) {
				if (abs(box.y - currentBox.y) < smallestBox.y) {
					smallestBox = box;
				}
				
			}

			destBox.y = currentBox.y < smallestBox.y ? smallestBox.y - currentBox.h : smallestBox.y + smallestBox.h;
		}
	}

	return Vector2{ destBox.x, destBox.y };
}

void PhysicsEngine::addCollidableElement(PhysicsElement* element) {
	m_collidableElements.push_back(element);
}

void PhysicsEngine::step() {
	int frameTickDifference = SDL_GetTicks() - lastFrameTime;
	double timeElapsed = static_cast<double>(frameTickDifference) / 1000; // convert ms to s

	for (PhysicsElement* element : m_collidableElements) {
		if (element->isAnchored()) continue; // anchored elements don't move

		element->applyVelocity(element->getAcceleration()); // add velocity from acceleration vector

		Vector2 position = element->getPosition();
		Vector2 velocity = element->getVelocity();
		Vector2 normalVelocity = normalizeVector(velocity);
		double maxVelocity = element->getMaxVelocity();

		element->applyVelocity(velocity * -.1);
		velocity = element->getVelocity();

		if (getMagnitude(velocity) > maxVelocity) {
			element->setVelocity(normalizeVector(velocity) * maxVelocity); // normalize and scale to max velocity
			velocity = element->getVelocity(); // update to new velocity
		}

		std::cout << velocity.x << "; " << velocity.y << std::endl;
		double newPosX = position.x + velocity.x * timeElapsed;
		double newPosY = position.y + velocity.y * timeElapsed;
		element->setPosition(getNearestValidCoords(element, newPosX, newPosY));
	}

	lastFrameTime = SDL_GetTicks();
}

double PhysicsEngine::getMagnitude(const Vector2& vector) {
	return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

Vector2 PhysicsEngine::normalizeVector(const Vector2& vector) {
	double magnitude = getMagnitude(vector);

	if (magnitude == 0) return vector;
	return Vector2{ vector.x / magnitude, vector.y / magnitude };
}