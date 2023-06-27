// Responsible for managing high level components and handling events
#pragma once

#include <string>
#include <set>
#include <stack>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDLUtils.h"
#include "IClickable.h"
#include "IHoverable.h"

class GameState; // forward declaration for circular dependency

class Engine {
	private:
		/* Engine Constants */


		// Window Constants
		inline static const int WINDOW_WIDTH = 1000;
		inline static const int WINDOW_HEIGHT = 500;
		inline static const int WINDOW_DEFAULT_XPOS = SDL_WINDOWPOS_UNDEFINED;
		inline static const int WINDOW_DEFAULT_YPOS = SDL_WINDOWPOS_UNDEFINED;
		inline static const int WINDOW_FLAGS = SDL_WINDOW_SHOWN;

		// Renderer constants
		const int RENDERER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

		// Engine member variables
		std::set<IClickable*>* clickableElements;
		std::set<IHoverable*>* hoverableElements;
		std::stack<GameState*> gameStates;
		SDL_Window* mainWindow;
		SDL_Renderer* renderer;

		// Engine state variables
		std::set<IHoverable*> currentlyHoveredElements;

		/* private member methods */


		// returns whether the given x,y is contained within the target rectangle.
		// the edge is included
		bool pointContainedInBox(const SDL_Rect& target, int queryX, int queryY);

	public:
		// where components are destroyed
		~Engine();

		Engine() : clickableElements{ nullptr }, hoverableElements{ nullptr }, 
			mainWindow(nullptr), renderer(nullptr) {};
		/* Init/Game loop functions */


		// Initializes the main window and rendering context we will use throughout game
		// window and renderer reference parameters updated with new components
		// returns true on success false on failure
		bool initializeComponents(const std::string& appName = "");

		// change the games current state. Must use this before starting engine to set initial state
		void pushGameState(GameState* state);

		// Handle relevant user inputs / events for current game state
		// Returns bool which indicates whether application should quit
		bool handleEvents();

		// Responsible for rendering current frame based on current game state
		
		void renderFrame();

		//reponsible for clearing game state stack to prepare for shutdown.
		void cleanup();


		/* Engine functions */

		// get the engine's renderer
		SDL_Renderer* getRenderer();
};