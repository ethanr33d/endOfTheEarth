// Interface that defines required functions for game states
#pragma once

#include <functional>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "Engine.h"

class GameState {
	private:

	protected:
		Engine& m_engine;
		std::set<IClickable*> m_clickableElements;
		std::set<IHoverable*> m_hoverableElements;
		std::set<IKeyboardListener*> m_keyboardListeners;
		std::set<IHoverable*> m_currentlyHoveredElements;
		
		// must call these functions to register elements so engine knows to check them for events
		void registerClickable(IClickable* element);
		void registerHoverable(IHoverable* element);
		void registerKeyboardListener(IKeyboardListener* element);
	public:
		GameState(Engine& eng) : m_engine(eng) {};
		virtual void drawFrame() = 0;
		virtual ~GameState() {}; // so derived classes get properly destroyed
		std::set<IClickable*>* getClickableElements();
		std::set<IHoverable*>* getHoverableElements();
		std::set<IKeyboardListener*>* getKeyboardListeners();
		std::set<IHoverable*>* getCurrentlyHoveredElements();
};