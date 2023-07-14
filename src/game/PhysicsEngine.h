#pragma once

#include <vector>
#include <cmath>
#include "PhysicsElement.h"
#include "Vector2.h"
#include "PhysicsRect.h"

class PhysicsEngine {
	private:
	std::vector<PhysicsElement*> m_collidableElements;
	int lastFrameTime;
	std::vector<PhysicsRect> getCollisions(const PhysicsRect& queryRect, const PhysicsElement* ignoreElement = nullptr);

	public:
		// return the nearest valid coordinates to desiredBounds such that there are no collisions 
		// between any objects. 
		// NOTE: Assumes that currentBounds are valid. 
		PhysicsEngine() : lastFrameTime(0) {};
		Vector2 getNearestValidCoords(const PhysicsElement* element, const double destX, const double destY);
		void addCollidableElement(PhysicsElement* element);
		void step();

		/* general use physics functions */

		// get magnitude of a vector
		static double getMagnitude(const Vector2& vector);

		// normalize vector to length of 1
		static Vector2 normalizeVector(const Vector2& vector);
};

