#include "Engine.h"
#include "GameState.h"

// private member methods

Engine::~Engine() {
	if (mainWindow) SDL_DestroyWindow(mainWindow);
	if (renderer) SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
}

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

void Engine::pushGameState(GameState* state) {
	gameStates.push(state);
	clickableElements = state->getClickableElements();
	hoverableElements = state->getHoverableElements();
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
			for (IClickable* element : *clickableElements) {
				SDL_Rect elementBox = element->getClickBox();
				bool contained = pointContainedInBox(elementBox, event.button.x, event.button.y);

				if (contained) {
					if (event.type == SDL_MOUSEBUTTONDOWN) element->mouseDown();
					if (event.type == SDL_MOUSEBUTTONUP) element->mouseUp();
				}
			}
			break;
		case SDL_MOUSEMOTION:

			// hover events (pseudo mouseEnter & mouseLeave events)
			for (IHoverable* element : *hoverableElements) {
				SDL_Rect elementBox = element->getHoverBox();
				bool contained = pointContainedInBox(elementBox, event.motion.x, event.motion.y);

				if (contained) { // check if we need to fire mouseEnter
					bool mouseEntered = true;

					// check if mouse already hovering over element
					if (currentlyHoveredElements.find(element) != currentlyHoveredElements.end()) {
						mouseEntered = false; // mouseEntered event has already fired	
					}
					
					if (mouseEntered) { // if mouseEntered has not already fired
						currentlyHoveredElements.insert(element);
						element->mouseEnter();
					}
					
				}
				else { // check if we need to fire mouseLeave
					bool mouseLeft = false;

					// check to see if we are tracking element for a leave event
					if (currentlyHoveredElements.find(element) != currentlyHoveredElements.end()) {
						mouseLeft = true;
					}

					if (mouseLeft) {
						currentlyHoveredElements.erase(element);
						element->mouseLeave();
					}
				}
			}
		}
	}

	return false; // don't quit by default
}

void Engine::renderFrame() {
	gameStates.top()->drawFrame();
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

void Engine::cleanup() {
	while (!gameStates.empty()) {
		gameStates.pop();
	}
}

SDL_Renderer* Engine::getRenderer() {
	return renderer;
}