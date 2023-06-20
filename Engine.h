#pragma once

#include <vector>
#include "SDL2/SDL.h"
#include "Button.h"

class Engine {
	private:
		// Engine Constants

		// 1. Window Constants
		inline static const int WINDOW_WIDTH = 1000;
		inline static const int WINDOW_HEIGHT = 500;
		inline static const int WINDOW_DEFAULT_XPOS = SDL_WINDOWPOS_UNDEFINED;
		inline static const int WINDOW_DEFAULT_YPOS = SDL_WINDOWPOS_UNDEFINED;
		inline static const int WINDOW_FLAGS = SDL_WINDOW_SHOWN;

		// 2. Renderer constants
		const int RENDERER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

		// Engine member variables
		std::vector<IClickable> clickableElements;
		SDL_Window* mainWindow;
		SDL_Renderer* renderer;

	public:
		// Initializes the main window and rendering context we will use throughout game
		// window and renderer reference parameters updated with new components
		// returns true on success false on failure
		bool initializeComponents(std::string appName);

		// Handle relevant user inputs / events for current game state
		// Returns bool which indicates whether application should quit
		bool handleEvents();

		// Responsible for rendering current frame based on current game state
		
		void renderFrame();

		//reponsible for cleaning up engine components. Should be called on shutdown.
		void cleanup();
};