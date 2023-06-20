#include "Engine.h"

bool Engine::initializeComponents(std::string appName) {
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
	mainWindow = SDL_CreateWindow(appName.c_str(),
		WINDOW_DEFAULT_XPOS,
		WINDOW_DEFAULT_YPOS,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		WINDOW_FLAGS
	);

	if (!mainWindow) {
		SDLUtils::error("SDL_CreateWindow");
		return false;
	}

	// Create rendering context
	renderer = SDL_CreateRenderer(mainWindow, -1, RENDERER_FLAGS);

	if (!renderer) {
		SDLUtils::error("SDL_CreateRenderer");
		return false;
	}

	return true;
}

bool Engine::handleEvents() {
	SDL_Event event{};

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return true;
		}
	}

	return false; // don't quit by default
}

void Engine::renderFrame() {
	// test case
	Button newButton("Menu");
	newButton.setSize(200, 100);
	newButton.setPosition(450, 250);
	newButton.show();
	newButton.render(renderer);

	Button newButton2("swalalala");
	newButton2.setSize(400, 200);
	newButton2.setPosition(5, 5);
	newButton2.show();
	newButton2.render(renderer);

	Button newButton3("Settings");
	newButton3.setSize(50, 100);
	newButton3.setPosition(700, 350);
	newButton3.show();
	newButton3.render(renderer);

	Button newButton4("Menu");
	newButton4.setSize(200, 200);
	newButton4.setPosition(50, 250);
	newButton4.show();
	newButton4.render(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255);

	SDL_RenderPresent(renderer); // show new frame
	SDL_RenderClear(renderer);
}

void Engine::cleanup() {
	if (mainWindow) SDL_DestroyWindow(mainWindow);
	if (renderer) SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
}