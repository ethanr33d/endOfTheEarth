#include "Player.h"
#include <iostream>
void Player::adjustMovementMatrix(SDL_Keycode key, double relativeSpeed, int time) {
	switch (key) {
		case MOVE_UP_KEY:
			// reset acceleration to make sure multiple key down/up doesn't double movespeed
			applyAcceleration(Vector2{ 0, m_movementMatrix.moveUp });
			m_movementMatrix.moveUp = relativeSpeed;
			m_movementMatrix.upKeyTime = time;
			applyAcceleration(Vector2{ 0, -relativeSpeed }); // up = negative Y
			break;
		case MOVE_RIGHT_KEY:
			applyAcceleration(Vector2{ -m_movementMatrix.moveRight, 0 });
			m_movementMatrix.moveRight = relativeSpeed;
			m_movementMatrix.rightKeyTime = time;
			applyAcceleration(Vector2{ relativeSpeed, 0 });
			break;
		case MOVE_DOWN_KEY:
			applyAcceleration(Vector2{ 0, -m_movementMatrix.moveDown });
			m_movementMatrix.moveDown = relativeSpeed;
			m_movementMatrix.downKeyTime = time;
			applyAcceleration(Vector2{ 0, relativeSpeed });
			break;
		case MOVE_LEFT_KEY:
			applyAcceleration(Vector2{ m_movementMatrix.moveLeft, 0 });
			m_movementMatrix.moveLeft = relativeSpeed;
			m_movementMatrix.leftKeyTime = time;
			applyAcceleration(Vector2{ -relativeSpeed, 0 }); // right = negative X
			break;
	}
}

void Player::keyDown(SDL_Keycode key) {
	adjustMovementMatrix(key, MOVE_ACCELERATION, SDL_GetTicks()); // move if key is down
}

void Player::keyUp(SDL_Keycode key) {
	adjustMovementMatrix(key, 0); // stop moving if key is up
}

void Player::draw() {
	SDL_Rect drawBounds = getIntCastedBounds();
	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(m_renderer, &drawBounds);
}