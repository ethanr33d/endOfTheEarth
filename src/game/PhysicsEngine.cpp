#include "PhysicsEngine.h"
#include <iostream>

std::vector<PhysicsRect> PhysicsEngine::getCollisions(const PhysicsRect& queryRect, const PhysicsElement* ignoreElement) {
	std::vector<PhysicsRect> collidingElements;

	for (PhysicsElement* element : m_physicsElements) {
		// check if element is collidable and element is not ignored
		if (!element->isCollidable() || element == ignoreElement) continue; 
		
		PhysicsRect eleBounds = element->getBounds();

		// if colliding on both x and y axis then they are truely colliding
		if (queryRect.x < eleBounds.x + eleBounds.w && queryRect.x + queryRect.w > eleBounds.x
				&& queryRect.y < eleBounds.y + eleBounds.h  && queryRect.y + queryRect.h > eleBounds.y) {

			collidingElements.push_back(eleBounds);
		}
	}

	return collidingElements;
}

double PhysicsEngine::getValidTranslationCoordByAxis(const PhysicsElement* element, AXIS targetAxis, const double destPos) {
	PhysicsRect currentBox = element->getBounds();
	
	double PhysicsRect::* axis{};
	double PhysicsRect::* size{};

	switch (targetAxis) {
		case X_AXIS:
			axis = &PhysicsRect::x;
			size = &PhysicsRect::w;
			break;
		case Y_AXIS:
			axis = &PhysicsRect::y;
			size = &PhysicsRect::h;
			break;
	}

	double resultPos = currentBox.*axis; // default to old position

	// if no change desired on axis skip checking
	if (destPos != currentBox.*axis) {

		// create a query rectangle between currentPos and destPos to find elements blocking path
		PhysicsRect queryRect = currentBox;

		queryRect.*axis = currentBox.*axis + currentBox.*size; // positions queryRect at end of currrentBox
		queryRect.*size = abs(destPos - currentBox.*axis); // size of queryRect is the difference in position

		if (destPos < currentBox.*axis) { // if destPos currentBox position, back queryRect up before currentBox
			queryRect.*axis = destPos;
		}

		std::vector<PhysicsRect> collisions = getCollisions(queryRect, element);

		if (collisions.size() == 0) { // path is clear
			resultPos = destPos; 
		} else { // there is a collision, find the nearest one
			PhysicsRect smallestBox{ 0, 0, 0, 0 };
			double smallestDist = INT_MAX;

			// find the nearest collision to currentPos
			for (const PhysicsRect& box : collisions) {
				// take the smaller of the distances to the top/bottom or left/right sides of the box
				double dist = fmin(abs(box.*axis - currentBox.*axis), abs(box.*axis + box.*size - currentBox.*axis));

				if (dist < smallestDist) {
					smallestBox = box;
					smallestDist = dist;
				}
			}

			// back destRect up so it doesn't collide with smallestBox
			// if currentPosition < collisionPosition adjust box to before collision, otherwise move it after
			resultPos = currentBox.*axis < smallestBox.*axis ? 
				smallestBox.*axis - currentBox.*size : smallestBox.*axis + smallestBox.*size;
		}
	}

	return resultPos;
}

void PhysicsEngine::addPhysicsElement(PhysicsElement* element) {
	m_physicsElements.insert(element);
}

void PhysicsEngine::step() {
	int frameTickDifference = SDL_GetTicks() - lastFrameTime;
	double timeElapsed = static_cast<double>(frameTickDifference) / 1000; // convert ms to s

	for (PhysicsElement* element : m_physicsElements) {
		if (element->isAnchored()) continue; // anchored elements don't move

		element->applyVelocity(element->getAcceleration()); // add velocity from acceleration vector

		Vector2 position = element->getPosition();
		Vector2 velocity = element->getVelocity();
		Vector2 normalVelocity = normalizeVector(velocity);
		double maxVelocity = element->getMaxVelocity();

		element->applyVelocity(velocity * -.25); // Temporary global friction (otherwise newton's first law)
		velocity = element->getVelocity();

		if (getMagnitude(velocity) > maxVelocity) {
			element->setVelocity(normalizeVector(velocity) * maxVelocity); // normalize and scale to max velocity
			velocity = element->getVelocity(); // update to new velocity
		}

		double newPosX = position.x + velocity.x * timeElapsed;
		double newPosY = position.y + velocity.y * timeElapsed; // calculate new position from velocity
		
		if (element->isCollidable()) { // if collidable make collision checks, else directly set pos
			Vector2 collisionAdjustedPos = position;
			
			// checks for collisions axis by axis. It is possible to clip certain corners since
			// each axis is checked and fixed indenpendently, but unlikely unless moving at
			// high speed or lagging
			
			// fix x axis
			collisionAdjustedPos.x = getValidTranslationCoordByAxis(element, X_AXIS, newPosX);
			element->setPosition(collisionAdjustedPos);

			// fix y axis
			collisionAdjustedPos.y = getValidTranslationCoordByAxis(element, Y_AXIS, newPosY);
			element->setPosition(collisionAdjustedPos);
			std::cout << collisionAdjustedPos.x << "," << collisionAdjustedPos.y << std::endl;
		}
		else {
			element->setPosition(Vector2{newPosX, newPosY});
		}
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