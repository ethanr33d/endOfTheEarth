// for animating physics objects

#pragma once

#include "SDL2/SDL.h"
#include "../SDLUtils.h"
#include "PhysicsElement.h"
#include "PhysicsEngine.h" // for math functions
#include <fstream>
#include <vector>

// struct for data on a specific aniamtion
struct AnimationSpriteData {
	int frameCount; // how many frames are in the animation
};
struct AnimationSpritesheetData {
	int spriteSizeX; // size of sprite for rendering
	int spriteSizeY;
	int collisionBoxX; // size of the collision box for physics purposes
	int collisionBoxY;

	std::vector<AnimationSpriteData> animData;

	AnimationSpritesheetData() : spriteSizeX(0), spriteSizeY(0), collisionBoxX(0),
		collisionBoxY(0) {};
};

class Animator {
	private:
		// ANIM_TYPE_COUNT for count of animation 
		enum ANIMATION_STATE {IDLE, WALKING, JUMPING, ANIM_STATE_COUNT};

		SDL_Renderer* m_renderer;
		SDL_Texture* m_spriteSheet;
		AnimationSpritesheetData m_sheetData;
		PhysicsElement* m_rig;

		ANIMATION_STATE m_animState;
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