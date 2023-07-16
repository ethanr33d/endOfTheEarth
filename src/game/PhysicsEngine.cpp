#include "PhysicsEngine.h"
#include <iostream>

std::vector<PhysicsElement*> PhysicsEngine::getCollisions(const PhysicsRect& queryRect,
	const PhysicsElement* ignoreElement) {
	std::vector<PhysicsElement*> collidingElements;

	for (PhysicsElement* element : m_physicsElements) {
		// check if element is collidable and element is not ignored
		if (!element->isCollidable() || element == ignoreElement) continue; 
		
		PhysicsRect eleBounds = element->getBounds();

		// if colliding on both x and y axis then they are truely colliding
		if (queryRect.x < eleBounds.x + eleBounds.w && queryRect.x + queryRect.w > eleBounds.x
				&& queryRect.y < eleBounds.y + eleBounds.h  && queryRect.y + queryRect.h > eleBounds.y) {

			collidingElements.push_back(element);
		}
	}

	return collidingElements;
}

PhysicsEngine::ValidTranslationCoordResult PhysicsEngine::getValidTranslationCoordByAxis(const PhysicsElement* element,
	AXIS targetAxis, const double destPos) {
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
	PhysicsElement* nearestCollision = nullptr; // default = no collision

	// if no change desired on axis skip checking
	if (destPos != currentBox.*axis) {

		// create a query rectangle between currentPos and destPos to find elements blocking path
		PhysicsRect queryRect = currentBox;

		queryRect.*axis = currentBox.*axis + currentBox.*size; // positions queryRect at end of currrentBox
		queryRect.*size = abs(destPos - currentBox.*axis); // size of queryRect is the difference in position

		if (destPos < currentBox.*axis) { // if destPos currentBox position, back queryRect up before currentBox
			queryRect.*axis = destPos;
		}

		std::vector<PhysicsElement*> collisions = getCollisions(queryRect, element);

		if (collisions.size() == 0) { // path is clear
			resultPos = destPos; 
		} else { // there is a collision, find the nearest one
			double smallestDist = INT_MAX;
			nearestCollision = collisions[0]; // prevent nullptr dereference

			// find the nearest collision to currentPos
			for (PhysicsElement* collidingElement : collisions) {
				PhysicsRect box = collidingElement->getBounds();
				// take the smaller of the distances to the top/bottom or left/right sides of the box
				double dist = fmin(abs(box.*axis - currentBox.*axis), abs(box.*axis + box.*size - currentBox.*axis));

				if (dist < smallestDist) {
					nearestCollision = collidingElement;
					smallestDist = dist;
				}
			}

			PhysicsRect smallestBox = nearestCollision->getBounds();
			// back destRect up so it doesn't collide with smallestBox
			// if currentPosition < collisionPosition adjust box to before collision, otherwise move it after
			resultPos = currentBox.*axis < smallestBox.*axis ?
				smallestBox.*axis - currentBox.*size : smallestBox.*axis + smallestBox.*size;
		}
	}

	return ValidTranslationCoordResult{ resultPos, nearestCollision };
}

void PhysicsEngine::addPhysicsElement(PhysicsElement* element) {
	m_physicsElements.insert(element);
}

void PhysicsEngine::step() {
	int frameTickDifference = SDL_GetTicks() - lastFrameTime;
	double timeElapsed = static_cast<double>(frameTickDifference) / 1000; // convert ms to s

	for (PhysicsElement* element : m_physicsElements) {
		if (element->isAnchored()) continue; // anchored elements don't move

		element->applyVelocity(element->getAcceleration() * timeElapsed); // add velocity from acceleration vector
		//std::cout << "velAdded" << element->getAcceleration() * timeElapsed;
		Vector2 position = element->getPosition();
		Vector2 velocity = element->getVelocity();
		Vector2 normalVelocity = normalizeVector(velocity);
		Vector2 maxVelocity = element->getMaxVelocity();
		double friction = AIR_RESISTANCE * GRAVITY * timeElapsed;

		if (element->isGrounded()) {
			friction = element->getGroundingElement()->getFrictionConstant() * GRAVITY * timeElapsed;
			//std::cout << "friction:" << friction;
		}

		if (abs(velocity.x) > friction) {
			// apply kinetic friction in direction opposite motion
			element->applyVelocity(Vector2{ -copysign(friction, velocity.x), 0 });
		}
		else {
			//static friction overcomes motion
			element->setVelocity(Vector2{ 0, velocity.y });
		}

		element->applyVelocity(Vector2{ 0, GRAVITY } *timeElapsed); // gravity
		velocity = element->getVelocity();

		// clamp axial velocities to their respective maximums
		element->setVelocity(Vector2{ SDL_clamp(velocity.x, -maxVelocity.x, maxVelocity.x),
			SDL_clamp(velocity.y, -maxVelocity.y, maxVelocity.y) });
		velocity = element->getVelocity();

		double newPosX = position.x + velocity.x * timeElapsed;
		double newPosY = position.y + velocity.y * timeElapsed; // calculate new position from velocity
		
		if (element->isCollidable()) { // if collidable make collision checks, else directly set pos
			Vector2 collisionAdjustedPos = position;
			
			// checks for collisions axis by axis. It is possible to clip certain corners since
			// each axis is checked and fixed indenpendently, but unlikely unless moving at
			// high speed or lagging
			
			// fix x axis
			ValidTranslationCoordResult XTranslationReq = getValidTranslationCoordByAxis(element, X_AXIS, newPosX);
			collisionAdjustedPos.x = XTranslationReq.pos;
			element->setPosition(collisionAdjustedPos);

			// fix y axis
			ValidTranslationCoordResult YTranslationReq = getValidTranslationCoordByAxis(element, Y_AXIS, newPosY);
			collisionAdjustedPos.y = YTranslationReq.pos;
			element->setPosition(collisionAdjustedPos);

			// if x collided with an element, reset velocity to 0
			if (XTranslationReq.collidingElement) {
				element->setVelocity(Vector2{ 0, velocity.y });
				velocity.x = 0;
			}

			// if y collided with an element from below, reset velocity to 0 and ground element
			if (YTranslationReq.collidingElement) {
				element->setVelocity(Vector2{ velocity.x, 0 });

				// if collision adjusted is less than requested, element must have hit ground
				if (collisionAdjustedPos.y < newPosY) {
					element->setGroundingElement(YTranslationReq.collidingElement);
					element->setGrounded(true); 
				}
			}
			else {
				// avoid redundant calls if element is already in free fall
				if (element->isGrounded()) {
					element->setGrounded(false);
				}
			}
		}
		else {
			element->setPosition(Vector2{newPosX, newPosY});
		}

		//std::cout << "ground: " << element->getGroundingElement() << ";";
		//std::cout << "Acceleration: " << element->getAcceleration() << "; Velocity: " << element->getVelocity() << std::endl;
	}

	lastFrameTime = SDL_GetTicks();
}

double PhysicsEngine::magnitude(const Vector2& vector) {
	return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

Vector2 PhysicsEngine::normalizeVector(const Vector2& vector) {
	double vecMagnitude = magnitude(vector);

	if (vecMagnitude == 0) return vector;
	return Vector2{ vector.x / vecMagnitude, vector.y / vecMagnitude };
}