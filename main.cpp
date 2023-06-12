#include <iostream>
#include  "SDL2/SDL.h"
#include "SDLUtils.h"
#include "Button.h"
// Constants

//General
const char* GAME_NAME = "End of the Earth";

// Window constants
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 500;
const int WINDOW_DEFAULT_XPOS = SDL_WINDOWPOS_UNDEFINED;
const int WINDOW_DEFAULT_YPOS = SDL_WINDOWPOS_UNDEFINED;
const int WINDOW_FLAGS = SDL_WINDOW_SHOWN;

// Renderer constants
const int RENDERER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

// Initializes the main window and rendering context we will use throughout game
// window and renderer reference parameters updated with new components
// returns true on success false on failure
bool initializeComponents(SDL_Window* &window, SDL_Renderer* &renderer) {
	// initialize SDL and necessary subsystems
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDLUtils::error("SDL_Init");
		return false;
	}

	// initialize text library
	if (TTF_Init()) {
		SDLUtils::error("TTF_Init");
		return false;
	}
	// initialize our window
	window = SDL_CreateWindow(GAME_NAME,
		WINDOW_DEFAULT_XPOS,
		WINDOW_DEFAULT_YPOS,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		WINDOW_FLAGS
	);

	if (!window) {
		SDLUtils::error("SDL_CreateWindow");
		return false;
	}

	// Create rendering context
	renderer = SDL_CreateRenderer(window, -1, RENDERER_FLAGS);

	if (!renderer) {
		SDLUtils::error("SDL_CreateRenderer");
		SDL_DestroyWindow(window);
		return false;
	}

	return true;
}

// Handle relevant user inputs / events
// Returns bool which indicates whether application should quit
bool HandleEvents(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_Event event{};

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				return true;
		}
	}

	return false; // don't quit by default
}

void RenderFrame(SDL_Window* window, SDL_Renderer* renderer) {
	// test case
	Button newButton("hello world");
	newButton.setSize(200, 100);
	newButton.setPosition(400, 200);
	newButton.show();
	newButton.render(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255);
}

int main(int, char**) {
	SDL_Window* mainWindow = nullptr;
	SDL_Renderer* renderer = nullptr;

	if (!initializeComponents(mainWindow, renderer)) {
		SDL_Quit();
		return 1;
	}

	bool readyToQuit = false;

	while (!readyToQuit) {
		readyToQuit = HandleEvents(mainWindow, renderer); 
		RenderFrame(mainWindow, renderer);
		SDL_RenderPresent(renderer); // show new frame
		SDL_RenderClear(renderer);
	}

	//cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(mainWindow);
	TTF_Quit();
	SDL_Quit();
	return 0;
}