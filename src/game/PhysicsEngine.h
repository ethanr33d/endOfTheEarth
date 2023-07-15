#pragma once

#include <vector>
#include <set>
#include <cmath>
#include "PhysicsElement.h"
#include "Vector2.h"
#include "PhysicsRect.h"

class PhysicsEngine {
	private:
		enum AXIS {X_AXIS, Y_AXIS};
		std::set<PhysicsElement*> m_physicsElements; // all physics simulated elements

		int lastFrameTime;
		
		// get the rectangles of all elements colliding with queryRect, with optional ignore element
		// @param queryRect: rectangle to check collisions against
		// @param ignoreElement: element to ignore when checking collisions
		std::vector<PhysicsRect> getCollisions(const PhysicsRect& queryRect, const PhysicsElement* ignoreElement = nullptr);

	public:
		PhysicsEngine() : lastFrameTime(0) {};

		// return the nearest valid axial position for element that desires to move to destPos on the given axis.
		// will be in the interval [currentPosition, destPos] if following assumption holds true.
		// NOTE: Assumes that currentBounds are valid. If element is already colliding with another element 
		// it is not guaraunteed to produce a valid position
		// @param element: element to be translated
		// @param targetAxis: translation axis. Other axis is ignored during calculations
		// @param destPos: destination position along the target axis
		double getValidTranslationCoordByAxis(const PhysicsElement* element, AXIS targetAxis, 
			const double destPos);

		void addPhysicsElement(PhysicsElement* element);
		void step();

		/* general use physics functions */

		// get magnitude of a vector
		static double getMagnitude(const Vector2& vector);

		// normalize vector to length of 1
		static Vector2 normalizeVector(const Vector2& vector);
};

