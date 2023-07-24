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

void PhysicsElement::setAnchored(const bool anchored) {
	m_anchored = anchored;
}

void PhysicsElement::setCollidable(const bool collidable) {
	m_collidable = collidable;
}

void PhysicsElement::setMaxVelocity(const Vector2& maxVelocity) {
	m_maxVelocity = maxVelocity;
}

void PhysicsElement::setFrictionConstant(const double friction) {
	m_frictionConstant = friction;
}

void PhysicsElement::_setGrounded(const bool grounded) {
	m_grounded = grounded;
}

void PhysicsElement::_setGroundingElement(PhysicsElement* element) {
	m_groundedBy = element;
}

void PhysicsElement::setDrawablePosition(const Vector2& position) {
	m_drawablePosition = position;
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

bool PhysicsElement::isAnchored() const {
	return m_anchored;
}

bool PhysicsElement::isCollidable() const {
	return m_collidable;
}

Vector2 PhysicsElement::getMaxVelocity() const {
	return m_maxVelocity;
}

double PhysicsElement::getFrictionConstant() const {
	return m_frictionConstant;
}

bool PhysicsElement::isGrounded() const {
	return m_grounded;
}

PhysicsElement* PhysicsElement::getGroundingElement() const {
	return m_groundedBy;
}


SDL_Rect PhysicsElement::getRenderBounds() const {
	return SDL_Rect{ static_cast<int>(m_drawablePosition.x), 
		static_cast<int>(m_drawablePosition.y),
		static_cast<int>(m_size.x),
		static_cast<int>(m_size.y)
	};
}

PhysicsRect PhysicsElement::getBounds() const {
	return PhysicsRect{ m_position.x, m_position.y, m_size.x, m_size.y };
}

void PhysicsElement::prePhysicsStep() {
	return; // do nothing by default
}

void PhysicsElement::postPhysicsStep() {
	return; // do nothing by default
}