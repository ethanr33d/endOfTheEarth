#pragma once

#include "SDL2/SDL.h"
#include "PhysicsElement.h"
#include "../IKeyboardListener.h"
#include "PhysicsEngine.h"

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

		// state sructure used to calcuate acceleration to apply based on user input
		struct PlayerMovementMatrix {
			bool jump;
			bool moveLeft; 
			bool moveRight;
			PlayerMovementMatrix() : jump(false),
				moveLeft(false), moveRight(false) {}; // default initializer
		} m_movementMatrix;

		Vector2 m_inputAcceleration; // acceleration from keyboard sources 

		// calculate the net acceleration to apply from matrix
		void applyAccelerationFromMatrix();

		// handles movement updates from key input
		// @param key: key that was pressed
		// @param keyState: whether key was pressed down or up
		void adjustMovementMatrixFromInput(SDL_Keycode key, bool keyState);
	public:
		Player(SDL_Renderer* renderer) : PhysicsElement(renderer), m_inputAcceleration(Vector2())
		{ setMaxVelocity(Vector2{MOVE_SPEED, INT_MAX}); };

		virtual void setGrounded(const bool grounded) override; // process jumps if necessary
		virtual void keyDown(SDL_Keycode key);
		virtual void keyUp(SDL_Keycode key);
		virtual void draw();
};