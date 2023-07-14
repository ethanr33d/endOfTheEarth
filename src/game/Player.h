#pragma once

#include "SDL2/SDL.h"
#include "PhysicsElement.h"
#include "../IKeyboardListener.h"
#include "PhysicsEngine.h"

class Player : public PhysicsElement, public IKeyboardListener {
	private:
		// constants
		inline static const SDL_Keycode MOVE_UP_KEY = SDLK_w;
		inline static const SDL_Keycode MOVE_DOWN_KEY = SDLK_s;
		inline static const SDL_Keycode MOVE_LEFT_KEY = SDLK_a;
		inline static const SDL_Keycode MOVE_RIGHT_KEY = SDLK_d;
		inline static const double MOVE_SPEED = 300; // pixels per second
		inline static const double MOVE_ACCELERATION = 150; // how fast move speed is achieved

		struct PlayerMovementMatrix {
			double moveLeft; int leftKeyTime; // move___ = speed of movement in that direction
			double moveRight; int rightKeyTime; // keyTime = time key was pressed
			double moveUp; int upKeyTime;
			double moveDown; int downKeyTime;

			PlayerMovementMatrix() : moveLeft(false), leftKeyTime(0),
				moveRight(false), rightKeyTime(0),
				moveUp(false), upKeyTime(0),
				moveDown(false), downKeyTime(0) {}; // default initializer
		} m_movementMatrix;

		// when key event comes in, update matrix as appropriate.
		// @param key: key that was pressed
		// @param relativeSpeed: speed to move, relative to the direction of movement
		// @param time: time of event, unnecessary for keyUp
		void adjustMovementMatrix(SDL_Keycode key, double relativeSpeed, int time = 0);
	public:
		Player(SDL_Renderer* renderer) : PhysicsElement(renderer) { setMaxVelocity(MOVE_SPEED); };

		virtual void keyDown(SDL_Keycode key);
		virtual void keyUp(SDL_Keycode key);
		virtual void draw();
};