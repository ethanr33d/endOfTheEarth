#include "Engine.h"
#include "IGameState.h"

// private member methods

bool Engine::pointContainedInBox(const SDL_Rect& target, int queryX, int queryY) {
	bool Xcheck = (queryX >= target.x && queryX <= target.x + target.w) ? true : false;
	bool Ycheck = (queryY >= target.y && queryY <= target.y + target.h) ? true : false;

	return Xcheck && Ycheck;
}

// public member methods 

bool Engine::initializeComponents(const std::string& appName) {
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

void Engine::pushGameState(IGameState* state) {
	gameStates.push_back(state);
}

bool Engine::handleEvents() {
	SDL_Event event{};

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return true;
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			for (int i = 0; i < clickableElements.size(); i++) {
				IClickable* element = clickableElements[i];
				SDL_Rect elementBox = element->getClickBox();
				bool contained = pointContainedInBox(elementBox, event.button.x, event.button.y);

				if (contained) {
					if (event.type == SDL_MOUSEBUTTONDOWN) element->mouseDown();
					if (event.type == SDL_MOUSEBUTTONUP) element->mouseUp();
				}
			}
		}
	}

	return false; // don't quit by default
}

void Engine::renderFrame() {
	gameStates[0]->drawFrame();
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

void Engine::cleanup() {
	if (mainWindow) SDL_DestroyWindow(mainWindow);
	if (renderer) SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
}

void Engine::registerNewClickable(IClickable* element) {
	clickableElements.push_back(element);
}

SDL_Renderer* Engine::getRenderer() {
	return renderer;
}