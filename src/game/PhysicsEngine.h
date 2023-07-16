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
		
		// returns a list of all elements colliding with queryRect, with optional ignore element
		// @param queryRect: rectangle to check collisions against
		// @param ignoreElement: element to ignore when checking collisions
		std::vector<PhysicsElement*> getCollisions(const PhysicsRect& queryRect,
			const PhysicsElement* ignoreElement = nullptr);

	public:
		inline static const double GRAVITY = 2000.0; // gravity acceleration const in px/s^2
		inline static const double AIR_RESISTANCE = 0.01; // friction constant for elements in freefall
		PhysicsEngine() : lastFrameTime(0) {};

		struct ValidTranslationCoordResult {
			double pos; // calculated valid position in translation, on interval [currentPos, destPos]
			PhysicsElement* collidingElement; // element that blocked complete translation, null if none
		};

		// return a ValidTranslationCoordResult that contains the nearest valid axial position for element that 
		// desires to move to destPos on the given axis, as well as the element that blocked the complete translation
		// if any. Returned pos will be in the interval [currentPosition, destPos] if following assumption holds true.
		// Mainly used for checking for collisions with moving objects
		// NOTE: Assumes that currentBounds are valid. If element is already colliding with another element 
		// it is not guaraunteed to produce a valid position
		// @param element: element to be translated
		// @param targetAxis: translation axis. Other axis is ignored during calculations
		// @param destPos: destination position along the target axis
		ValidTranslationCoordResult getValidTranslationCoordByAxis(const PhysicsElement* element, 
			AXIS targetAxis, const double destPos);

		void addPhysicsElement(PhysicsElement* element);
		void step();

		/* general use physics functions */

		// get magnitude of a vector
		static double magnitude(const Vector2& vector);

		// normalize vector to length of 1
		static Vector2 normalizeVector(const Vector2& vector);
};

