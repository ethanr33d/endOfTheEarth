// for animating physics objects

#pragma once

#include "SDL2/SDL.h"
#include "../SDLUtils.h"
#include "PhysicsElement.h"
#include "PhysicsEngine.h" // for math functions
#include <fstream>
#include <vector>

// Animation sprite sheets should have animations in this order:
// 1. Idle
// 2. Walk
// 3. Jump
// 4. Freefall
// 
// spriteData files take the following form:
// First 2 numbers: sprite size (ex: 32x32)
// Numbers 3 and 4: Collision box size of sprite (w,h)
// Numbers 5 and 6: Pixel offset to the collision box on x-axis, i.e distance in px to drawing from
//     the left and right side of the sprite
// Numbers 7 and 8: same as 5 and 6 but for Y
// Numers 9+: data for each animation in pairs according to animation order (frameCount, playbackSpeed)



// struct for data on a specific aniamtion
struct AnimationSpriteData {
	int frameCount; // how many frames are in the animation
	int basePlaybackSpeed; // speed in ms between frame changes
};

struct AnimationSpritesheetData {
	int spriteSizeX; // size of sprite for rendering
	int spriteSizeY;
	int collisionBoxX; // size of the collision box for physics purposes
	int collisionBoxY;
	int drawOffsetLeftX;
	int drawOffsetRightX;
	int drawOffsetTopY;
	int drawOffsetBottomY;

	std::vector<AnimationSpriteData> animData;

	AnimationSpritesheetData() : spriteSizeX(0), spriteSizeY(0), collisionBoxX(0),
		collisionBoxY(0), drawOffsetLeftX(0), drawOffsetRightX(0), drawOffsetTopY(0), 
		drawOffsetBottomY(0) {};
};

class Animator {
	private:
		// ANIM_TYPE_COUNT for count of animation 
		enum ANIMATION_STATE {IDLE, WALKING, JUMPING, FREE_FALL, ANIM_STATE_COUNT};

		// min > max since this multiplies with frame rate (bigger factor = longer time between frames)
		inline static const double MIN_WALKING_SPEEDFACTOR = 1.5; // minimum playback multiplier for walking 
		inline static const double MAX_WALKING_SPEEDFACTOR = 0.5; // maximum playback multiplier (character going fast)

		SDL_Renderer* m_renderer;
		SDL_Texture* m_spriteSheet; // current loaded sheet
		AnimationSpritesheetData m_sheetData;
		PhysicsElement* m_rig;

		ANIMATION_STATE m_animState; // current animation state
		double m_playbackMultiplier; // multiplier on top of base playback in certain cases (ex: walking)
		int m_animFrameNumber; // frame number of current frame in the animation
		int m_lastFrame; // time since last animation frame
		bool m_flipAnim; // if animation should be flipped (because player is looking another direction)

		// determines what the state of the player should be for animation purposes
		// updates m_animState and m_flipAnim
		void  decideAnimState();
	public:
		// file paths to the sprite sheet to be used and the corresponding
		// spriteData file
		Animator(const std::string& sheet, const std::string& sheetData, SDL_Renderer* renderer, 
			PhysicsElement* element);
	
		// animate an element based on it's current state. Should be called during the post physics step
		void animate();

		// get the frame in the current animation to render to the screen
		void drawAnimationFrame();

		// animate an element 
		void playAnimation();

		// get the appropriate width and height for the collision box of the loaded animation sheet
		// takes into account if the element has been scaled from sprite size
		Vector2 getCollisionSizeFromSheet();
};