// Interface that defines required functions for game states
#pragma once

#include <functional>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "Engine.h"

class GameState {
	private:

	protected:
		Engine& engine;
		std::set<IClickable*> clickableElements;
		std::set<IHoverable*> hoverableElements;

		// must call these functions to register elements so engine knows to check them for events
		void registerClickable(IClickable* element);
		void registerHoverable(IHoverable* element);
	public:
		GameState(Engine& eng) : engine(eng) {};
		virtual void drawFrame() = 0;
		virtual ~GameState() {}; // so derived classes get properly destroyed
		std::set<IClickable*>* getClickableElements();
		std::set<IHoverable*>* getHoverableElements();
};