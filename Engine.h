#pragma once

#include <vector>
// Responsible for managing high level components and handling events

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDLUtils.h"
#include "IClickable.h"

class IGameState; // forward declaration for circular dependency

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
		std::vector<IClickable*> clickableElements;
		std::vector<IGameState*> gameStates;
		SDL_Window* mainWindow;
		SDL_Renderer* renderer;

		/* private member methods */


		// returns whether the given x,y is contained within the target rectangle.
		// the edge is included
		bool pointContainedInBox(const SDL_Rect& target, int queryX, int queryY);

	public:
		Engine() : mainWindow(nullptr), renderer(nullptr) {};
		/* Init/Game loop functions */


		// Initializes the main window and rendering context we will use throughout game
		// window and renderer reference parameters updated with new components
		// returns true on success false on failure
		bool initializeComponents(const std::string& appName = "");

		// change the games current state. Must use this before starting engine to set initial state
		void pushGameState(IGameState* state);

		// Handle relevant user inputs / events for current game state
		// Returns bool which indicates whether application should quit
		bool handleEvents();

		// Responsible for rendering current frame based on current game state
		
		void renderFrame();

		//reponsible for cleaning up engine components. Should be called on shutdown.
		void cleanup();


		/* Engine functions */

		// Register a new clickable element with the engine so it can begin to check
		// for click events with it
		void registerNewClickable(IClickable* newMember);

		// get the engine's renderer
		SDL_Renderer* getRenderer();
};