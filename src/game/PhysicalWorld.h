// contains all of the elements in a physics simulation
// various classes like physics engine and camera manipulate and/or
// read this class to draw the world

#pragma once

#include <set>
#include "PhysicsElement.h"

class PhysicalWorld {
	private:
		std::set<PhysicsElement*> m_physicsElements;

	public:
		// add element to simulation
		void addElement(PhysicsElement* element);

		// remove element
		void removeElement(PhysicsElement* element);

		// return the list of elements. Elements can be modified but the list cannot
		const std::set<PhysicsElement*>* getElements();
};