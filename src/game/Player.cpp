#include "Player.h"
#include <iostream>

void Player::applyAccelerationFromMatrix() {
	applyAcceleration(-m_inputAcceleration); // reset acceleration from input

	Vector2 newAcceleration;
	double friction = PhysicsEngine::AIR_RESISTANCE;

	if (m_grounded && m_groundedBy) {
		friction = m_groundedBy->getFrictionConstant();
	}

	newAcceleration.x = (-1 * m_movementMatrix.moveLeft + m_movementMatrix.moveRight) 
		* MOVE_ACCELERATION * friction;

	m_inputAcceleration = newAcceleration;
	applyAcceleration(newAcceleration);
}

void Player::adjustMovementMatrixFromInput(SDL_Keycode key, bool keyState) {
	switch (key) {
		case MOVE_UP_KEY:
		case SECONDARY_UP_KEY:
			m_movementMatrix.jump = keyState;
			break;
		case MOVE_RIGHT_KEY:
			m_movementMatrix.moveRight = keyState;
			applyAccelerationFromMatrix();
			break;
		case MOVE_LEFT_KEY:
			m_movementMatrix.moveLeft = keyState;
			applyAccelerationFromMatrix();
			break;
	}
}

void Player::setGrounded(const bool grounded) {
	PhysicsElement::setGrounded(grounded); // default behavior

	if (grounded && m_movementMatrix.jump) {
		applyVelocity(Vector2{ 0, -JUMP_POWER });
	}

	applyAccelerationFromMatrix(); // friction may have changed
}

void Player::keyDown(SDL_Keycode key) {
	adjustMovementMatrixFromInput(key, true); // move if key is down
}

void Player::keyUp(SDL_Keycode key) {
	adjustMovementMatrixFromInput(key, false); // stop moving if key is up
}

void Player::draw() {
	SDL_Rect drawBounds = getRenderPosition();
	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(m_renderer, &drawBounds);
}