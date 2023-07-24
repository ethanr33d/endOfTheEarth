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

Player::Player(SDL_Renderer* renderer) : PhysicsElement(renderer), m_inputAcceleration(Vector2()),
	animator(ANIMATION_SHEET, ANIMATION_SHEET_DATA, renderer, this) {
	setMaxVelocity(Vector2{ MOVE_SPEED, INT_MAX });
};

void Player::adjustMovementMatrixFromInput(SDL_Keycode key, bool keyState) {
	switch (key) {
		case MOVE_UP_KEY:
		case SECONDARY_UP_KEY:
			m_movementMatrix.jump = keyState;
			break;
		case MOVE_RIGHT_KEY:
			m_movementMatrix.moveRight = keyState;
			break;
		case MOVE_LEFT_KEY:
			m_movementMatrix.moveLeft = keyState;
			break;
	}
}

// do movement calculations
void Player::prePhysicsStep() {
	if (m_grounded && m_movementMatrix.jump) {
		applyVelocity(Vector2{ 0, -JUMP_POWER });
	}

	applyAccelerationFromMatrix();
}

void Player::postPhysicsStep() {
	animator.animate(); // calculate next animation frame
}

void Player::keyDown(SDL_Keycode key) {
	adjustMovementMatrixFromInput(key, true); // move if key is down
}

void Player::keyUp(SDL_Keycode key) {
	adjustMovementMatrixFromInput(key, false); // stop moving if key is up
}

void Player::draw() {
	animator.drawAnimationFrame();
}