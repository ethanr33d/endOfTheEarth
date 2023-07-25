#pragma once

#include "SDL2/SDL.h"
#include "../SDLUtils.h"
#include "PhysicsElement.h"
#include "../IKeyboardListener.h"
#include "PhysicsEngine.h"
#include "Animator.h"

class Player : public PhysicsElement, public IKeyboardListener {
	private:
		// constants
		inline static const SDL_Keycode MOVE_UP_KEY = SDLK_w;
		inline static const SDL_Keycode SECONDARY_UP_KEY = SDLK_SPACE;
		inline static const SDL_Keycode MOVE_LEFT_KEY = SDLK_a;
		inline static const SDL_Keycode MOVE_RIGHT_KEY = SDLK_d;
		inline static const double MOVE_SPEED = 300; // pixels per second
		inline static const double MOVE_ACCELERATION = 3000; // how fast move speed is achieved
		inline static const double JUMP_POWER = 700; // instant jump velocity
		inline static const std::string ANIMATION_SHEET = 
			SDLUtils::getResourceDirPath("entities\\player") + "larryAnimations.png";
		inline static const std::string ANIMATION_SHEET_DATA =
			SDLUtils::getResourceDirPath("entities\\player") + "larryAnimations.spriteData";

		// state sructure used to calcuate acceleration to apply based on user input
		struct PlayerMovementMatrix {
			bool jump;
			bool moveLeft; 
			bool moveRight;
			PlayerMovementMatrix() : jump(false),
				moveLeft(false), moveRight(false) {}; // default initializer
		} m_movementMatrix;

		Vector2 m_inputAcceleration; // acceleration from keyboard sources 
		Animator m_animator; // handles animations for player

		// calculate the net acceleration to apply from matrix
		void applyAccelerationFromMatrix();

		// handles movement updates from key input
		// @param key: key that was pressed
		// @param keyState: whether key was pressed down or up
		void adjustMovementMatrixFromInput(SDL_Keycode key, bool keyState);
	public:
		Player(SDL_Renderer* renderer);

		virtual void setSize(const Vector2& size) override; // need to rescale based on animation size
		virtual void prePhysicsStep();
		virtual void postPhysicsStep();
		virtual void keyDown(SDL_Keycode key);
		virtual void keyUp(SDL_Keycode key);
		virtual void draw();
};