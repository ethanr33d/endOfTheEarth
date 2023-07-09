#pragma once

#include "SDL2/SDL.h"
#include "../Drawable.h"
#include "../IKeyboardListener.h"
#include "PhysicsEngine.h"

class Player : public Drawable, public IKeyboardListener {
	private:
		// constants
		inline static const SDL_Keycode MOVE_UP_KEY = SDLK_w;
		inline static const SDL_Keycode MOVE_DOWN_KEY = SDLK_s;
		inline static const SDL_Keycode MOVE_LEFT_KEY = SDLK_a;
		inline static const SDL_Keycode MOVE_RIGHT_KEY = SDLK_d;
		inline static const double MOVE_SPEED = 250; // pixels per second

		PhysicsEngine& m_physicsEngine;

		struct PlayerMovementMatrix {
			bool moveLeft; int leftKeyTime; // keyTime = time key was pressed
			bool moveRight; int rightKeyTime;
			bool moveUp; int upKeyTime;
			bool moveDown; int downKeyTime;

			PlayerMovementMatrix() : moveLeft(false), leftKeyTime(0),
				moveRight(false), rightKeyTime(0),
				moveUp(false), upKeyTime(0),
				moveDown(false), downKeyTime(0) {}; // default initializer
		} m_movementMatrix;

		double m_exactXPos; // exact position for physics calculations
		double m_exactYPos;

		// when key event comes in, update matrix as appropriate
		void adjustMovementMatrix(SDL_Keycode key, bool moveInDirection, int time = 0);
	public:
		Player(SDL_Renderer* renderer, PhysicsEngine& physicsEngine) : Drawable(renderer),
			m_physicsEngine(physicsEngine), m_exactXPos(0.0), m_exactYPos(0.0) {};

		virtual void setPosition(const int newX, const int newY) override;
		virtual void keyDown(SDL_Keycode key);
		virtual void keyUp(SDL_Keycode key);
		virtual void draw();
};