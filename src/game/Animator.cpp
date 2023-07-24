#include "Animator.h"

void Animator::decideAnimState() {
	Vector2 velocity = m_rig->getVelocity();

	if (velocity.y < 0) { // negative Y = up on screen
		m_animState = JUMPING;
	}
	else if (abs(velocity.x) > 0) {
		m_animState = WALKING;
	}
	else {
		m_animState = IDLE;
	}

	// if velocity.x = 0 keep whatever flip value was previously stored
	if (velocity.x < 0) {
		m_flipAnim = true;
	} else if (velocity.x > 0) {
		m_flipAnim = false;
	}
}

Animator::Animator(const std::string& sheet, const std::string& sheetData, SDL_Renderer* renderer, 
	PhysicsElement* element) : m_renderer(renderer), m_spriteSheet(SDLUtils::loadTexture(renderer, sheet)), 
	m_rig(element), m_animState(IDLE), m_animFrameNumber(-1), m_lastFrame(0), m_flipAnim(false) {
	std::ifstream dataFile(sheetData);

	if (!dataFile) {
		SDLUtils::error("Animator::animator animation sheet data invalid");
	}

	dataFile >> m_sheetData.spriteSizeX;
	dataFile >> m_sheetData.spriteSizeY;
	dataFile >> m_sheetData.idleFrames;
	dataFile >> m_sheetData.walkFrames;
	dataFile >> m_sheetData.jumpFrames;
}

void Animator::animate() {
	ANIMATION_STATE oldState = m_animState;
	decideAnimState();
	int timeSinceLastFrame = SDL_GetTicks() - m_lastFrame;

	if (oldState != m_animState) {
		m_animFrameNumber = 0; // reset animation if this is a new state
	}

	if (timeSinceLastFrame > 100) {
		switch (m_animState) { // increment frame number / loop back to beginning
			case IDLE:
				(m_animFrameNumber += 1) %= m_sheetData.idleFrames;
				break;
			case WALKING:
				(m_animFrameNumber += 1) %= m_sheetData.walkFrames;
				break;
			case JUMPING:
				(m_animFrameNumber += 1) %= m_sheetData.jumpFrames;
				break;
		}

		m_lastFrame = SDL_GetTicks();
	}

}

void Animator::drawAnimationFrame() {
	SDL_Rect drawablePos = m_rig->getRenderBounds();

	SDL_Rect spriteClip{
		m_animFrameNumber * m_sheetData.spriteSizeX,
		m_animState * m_sheetData.spriteSizeY,
		m_sheetData.spriteSizeX,
		m_sheetData.spriteSizeY
	};

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	if (m_flipAnim) {
		flip = SDL_FLIP_HORIZONTAL;
	}

	SDL_RenderCopyEx(m_renderer, m_spriteSheet, &spriteClip, &drawablePos, 0, NULL, flip);
}

void Animator::playAnimation() {

}