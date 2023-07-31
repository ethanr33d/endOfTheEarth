#include "Animator.h"

void Animator::decideAnimState() {
	Vector2 velocity = m_rig->getVelocity();

	if (!m_rig->isGrounded()) { // freefall check
		if (velocity.y > 0) {
			m_animState = JUMPING;
			m_playbackMultiplier = 1;
		}
		else {
			m_animState = FREE_FALL;
			m_playbackMultiplier = 1;
		}
	}
	else if (abs(velocity.x) > 0) {
		m_animState = WALKING;
		// 1 / (% of max velocity player is at) * max speedup * friction of surface to make ice slippy slidy
		// clamped in the range MAX_FACTOR - MIN_FACTOR
		m_playbackMultiplier = SDL_clamp(
			(1 / (abs(velocity.x) / m_rig->getMaxVelocity().x)) * MAX_WALKING_SPEEDFACTOR
			* m_rig->getGroundingElement()->getFrictionConstant(),
			MAX_WALKING_SPEEDFACTOR,
			MIN_WALKING_SPEEDFACTOR
		);
		
		std::cout << m_playbackMultiplier << std::endl;
	}
	else {
		m_animState = IDLE;
		m_playbackMultiplier = 1;
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
	m_rig(element), m_animState(IDLE), m_playbackMultiplier(0), m_animFrameNumber(-1), m_lastFrame(0),
	m_flipAnim(false) {

	std::ifstream dataFile(sheetData);

	if (!dataFile) {
		SDLUtils::error("Animator::animator animation sheet data invalid");
	}

	dataFile >> m_sheetData.spriteSizeX;
	dataFile >> m_sheetData.spriteSizeY;
	dataFile >> m_sheetData.collisionBoxX;
	dataFile >> m_sheetData.collisionBoxY;
	dataFile >> m_sheetData.drawOffsetLeftX;
	dataFile >> m_sheetData.drawOffsetRightX;
	dataFile >> m_sheetData.drawOffsetTopY;
	dataFile >> m_sheetData.drawOffsetBottomY;

	for (int i = 0; i < ANIM_STATE_COUNT; i++) {
		AnimationSpriteData newAnim{};

		dataFile >> newAnim.frameCount;
		dataFile >> newAnim.basePlaybackSpeed;

		m_sheetData.animData.push_back(newAnim);
	}
}

void Animator::animate() {
	ANIMATION_STATE oldState = m_animState;
	decideAnimState();
	int timeSinceLastFrame = SDL_GetTicks() - m_lastFrame;

	if (oldState != m_animState) {
		m_animFrameNumber = 0; // reset animation if this is a new state
	}

	if (m_sheetData.animData[m_animState].basePlaybackSpeed * m_playbackMultiplier <= timeSinceLastFrame) {
		// add to frame number and wrap to 0 if necessary
		(m_animFrameNumber += 1) %= m_sheetData.animData[m_animState].frameCount; 
		m_lastFrame = SDL_GetTicks();
	}

}

void Animator::drawAnimationFrame() {
	SDL_Rect drawablePos = m_rig->getRenderBounds();

	// get specific frame of animation
	SDL_Rect spriteClip{ 
		m_animFrameNumber * m_sheetData.spriteSizeX,
		m_animState * m_sheetData.spriteSizeY,
		m_sheetData.spriteSizeX,
		m_sheetData.spriteSizeY
	};

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	double Xscale = static_cast<double>(drawablePos.w) / m_sheetData.spriteSizeX;
	double Yscale = static_cast<double>(drawablePos.h) / m_sheetData.spriteSizeY;

	int drawOffsetX = static_cast<int>(m_sheetData.drawOffsetLeftX * Xscale);
	int drawOffsetY = static_cast<int>(m_sheetData.drawOffsetTopY * Yscale);

	// Y flipping not yet supported
	if (m_flipAnim) {
		flip = SDL_FLIP_HORIZONTAL;
		drawOffsetX = static_cast<int>(m_sheetData.drawOffsetRightX * Xscale);
	}

	// offset drawing so it gets rendered on the ground
	drawablePos.x -= drawOffsetX;
	drawablePos.y -= drawOffsetY;
	SDL_RenderCopyEx(m_renderer, m_spriteSheet, &spriteClip, &drawablePos, 0, NULL, flip);
}

Vector2 Animator::getCollisionSizeFromSheet() {
	Vector2 resultVector;
	Vector2 currentSize = m_rig->getSize();

	// scaling factor * raw collision box size
	resultVector.x = currentSize.x / m_sheetData.spriteSizeX * m_sheetData.collisionBoxX;
	resultVector.y = currentSize.y / m_sheetData.spriteSizeY * m_sheetData.collisionBoxY;

	std::cout << resultVector << "," << currentSize << std::endl;
	return resultVector;
}

/* TODO:
void Animator::playAnimation() {

}

*/