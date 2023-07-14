#include "PhysicsElement.h"

void PhysicsElement::applyAcceleration(const Vector2& acceleration) {
	m_acceleration.x += acceleration.x;
	m_acceleration.y += acceleration.y;
}

void PhysicsElement::applyVelocity(const Vector2& velocity) {
	m_velocity.x += velocity.x;
	m_velocity.y += velocity.y;
}


void PhysicsElement::setSize(const Vector2& size) {
	m_size = size;
}

void PhysicsElement::setPosition(const Vector2& position) {
	m_position = position;
}

void PhysicsElement::setVelocity(const Vector2& velocity) {
	m_velocity = velocity;
}

void PhysicsElement::setAcceleration(const Vector2& acceleration) {
	m_acceleration = acceleration;
}

void PhysicsElement::setAnchored(const bool anchor) {
	m_anchored = anchor;
}

void PhysicsElement::setMaxVelocity(const double maxVelocity) {
	m_maxVelocity = maxVelocity;
}

Vector2 PhysicsElement::getSize() const {
	return m_size;
}

Vector2 PhysicsElement::getPosition() const {
	return m_position;
}

Vector2 PhysicsElement::getVelocity() const {
	return m_velocity;
}

Vector2 PhysicsElement::getAcceleration() const {
	return m_acceleration;
}

bool PhysicsElement::isAnchored() {
	return m_anchored;
}

double PhysicsElement::getMaxVelocity() {
	return m_maxVelocity;
}

SDL_Rect PhysicsElement::getIntCastedBounds() const {
	return SDL_Rect{ static_cast<int>(m_position.x), 
		static_cast<int>(m_position.y),
		static_cast<int>(m_size.x),
		static_cast<int>(m_size.y)
	};
}

PhysicsRect PhysicsElement::getBounds() const {
	return PhysicsRect{ m_position.x, m_position.y, m_size.x, m_size.y };
}