#include "PhysicalWorld.h"

void PhysicalWorld::addElement(PhysicsElement* element) {
	m_physicsElements.insert(element);
}

void PhysicalWorld::removeElement(PhysicsElement* element) {
	m_physicsElements.erase(element);
}

const std::set<PhysicsElement*>* PhysicalWorld::getElements() {
	return &m_physicsElements;
}