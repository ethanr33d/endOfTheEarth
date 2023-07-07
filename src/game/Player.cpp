#include "Player.h"

void Player::adjustMovementMatrix(SDL_Keycode key, bool moveInDirection, int time) {
	switch (key) {
		case MOVE_UP_KEY:
			m_movementMatrix.moveUp = moveInDirection;
			m_movementMatrix.upKeyTime = time;
			break;
		case MOVE_RIGHT_KEY:
			m_movementMatrix.moveRight = moveInDirection;
			m_movementMatrix.rightKeyTime = time;
			break;
		case MOVE_DOWN_KEY:
			m_movementMatrix.moveDown = moveInDirection;
			m_movementMatrix.downKeyTime = time;
			break;
		case MOVE_LEFT_KEY:
			m_movementMatrix.moveLeft = moveInDirection;
			m_movementMatrix.leftKeyTime = time;
			break;
	}
}
void Player::keyDown(SDL_Keycode key) {
	adjustMovementMatrix(key, true, SDL_GetTicks()); // move if key is down
}

void Player::keyUp(SDL_Keycode key) {
	adjustMovementMatrix(key, false); // stop moving if key is up
}

void Player::draw() {
	int time = SDL_GetTicks();

	// new position = old + (time since last frame or key pressed * move speed * isKeyDown) 
	// isKeyDown = 1 if true, 0 if false (negates movement)
	m_exactXPos = m_exactXPos - ((time - m_movementMatrix.leftKeyTime) * (MOVE_SPEED / 1000) * m_movementMatrix.moveLeft);
	m_exactXPos = m_exactXPos + ((time - m_movementMatrix.rightKeyTime) * (MOVE_SPEED / 1000) * m_movementMatrix.moveRight);
	m_exactYPos = m_exactYPos - ((time - m_movementMatrix.upKeyTime) * (MOVE_SPEED / 1000) * m_movementMatrix.moveUp);
	m_exactYPos = m_exactYPos + ((time - m_movementMatrix.downKeyTime) * (MOVE_SPEED / 1000) * m_movementMatrix.moveDown);

	// if key still down, set time to now so next frame only calculates position change since this frame
	if (m_movementMatrix.moveLeft) m_movementMatrix.leftKeyTime = time;
	if (m_movementMatrix.moveRight) m_movementMatrix.rightKeyTime = time;
	if (m_movementMatrix.moveUp) m_movementMatrix.upKeyTime = time;
	if (m_movementMatrix.moveDown) m_movementMatrix.downKeyTime = time;

	double xFrac = m_exactXPos - (int)m_exactXPos;
	double yFrac = m_exactYPos - (int)m_exactYPos;

	//setPosition(static_cast<int>(m_exactXPos), static_cast<int>(m_exactYPos));
	SDL_Rect physicsCheck = m_physicsEngine.getNearestValidCoords(this, (int)m_exactXPos, (int)m_exactYPos);
	setPosition(physicsCheck.x, physicsCheck.y);
	m_exactXPos = m_bounds.x + xFrac;
	m_exactYPos = m_bounds.y + yFrac;

	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(m_renderer, &m_bounds);
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
}