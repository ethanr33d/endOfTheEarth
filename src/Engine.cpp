#include "Engine.h"
#include "GameState.h"
#include "MainMenu.h"
#include "HelpScreen.h"

// private member methods

Engine::~Engine() {
	// clean state memory
	while (!m_gameStates.empty()) {
		GameState* stateToRemove = m_gameStates.top();
		m_gameStates.pop();

		delete stateToRemove;
	}

	// close libraries
	if (m_mainWindow) SDL_DestroyWindow(m_mainWindow);
	if (m_renderer) SDL_DestroyRenderer(m_renderer);
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
	m_mainWindow = SDL_CreateWindow(appName.c_str(),
		WINDOW_DEFAULT_XPOS,
		WINDOW_DEFAULT_YPOS,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		WINDOW_FLAGS
	);

	if (!m_mainWindow) {
		SDLUtils::error("SDL_CreateWindow");
		return false;
	}

	// Create rendering context
	m_renderer = SDL_CreateRenderer(m_mainWindow, -1, RENDERER_FLAGS);

	if (!m_renderer) {
		SDLUtils::error("SDL_CreateRenderer");
		return false;
	}

	return true;
}

void Engine::pushGameState(GAME_STATE state) {
	GameState* newState;
	switch (state) {
		case MAIN_MENU:
			newState = new MainMenu(*this);
			break;
		case HELP_SCREEN:
			newState = new HelpScreen(*this);
			break;
	}

	m_gameStates.push(newState);
	m_changingState = true;

	// set tracked elements to new state
	m_clickableElements = newState->getClickableElements();
	m_hoverableElements = newState->getHoverableElements();
}

void Engine::popGameState() {
	if (m_gameStates.size() <= 1) std::cerr << "No game state to pop back to" << std::endl;

	GameState* deadState = m_gameStates.top();

	m_gameStates.pop();
	m_changingState = true;
	delete deadState; // release memory

	// reset tracked elements to old state
	m_clickableElements = m_gameStates.top()->getClickableElements();
	m_hoverableElements = m_gameStates.top()->getHoverableElements();

}

bool Engine::handleEvents() {
	SDL_Event event{};
	m_changingState = false; // fresh event loop

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return true;
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			for (IClickable* element : *m_clickableElements) {
				SDL_Rect elementBox = element->getClickBox();
				bool contained = pointContainedInBox(elementBox, event.button.x, event.button.y);

				if (contained) {
					if (event.type == SDL_MOUSEBUTTONDOWN) element->mouseDown();
					if (event.type == SDL_MOUSEBUTTONUP) element->mouseUp();
					
					if (m_changingState) return false; // button press resulted in state change; abort
				}
			}
			break;
		case SDL_MOUSEMOTION:

			// hover events (pseudo mouseEnter & mouseLeave events)
			for (IHoverable* element : *m_hoverableElements) {
				SDL_Rect elementBox = element->getHoverBox();
				bool contained = pointContainedInBox(elementBox, event.motion.x, event.motion.y);

				if (contained) { // check if we need to fire mouseEnter
					bool mouseEntered = true;

					// check if mouse already hovering over element
					if (m_currentlyHoveredElements.find(element) != m_currentlyHoveredElements.end()) {
						mouseEntered = false; // mouseEntered event has already fired	
					}
					
					if (mouseEntered) { // if mouseEntered has not already fired
						m_currentlyHoveredElements.insert(element);
						element->mouseEnter();
						if (m_changingState) return false; // button call changed state; abort
					}
					
				}
				else { // check if we need to fire mouseLeave
					bool mouseLeft = false;

					// check to see if we are tracking element for a leave event
					if (m_currentlyHoveredElements.find(element) != m_currentlyHoveredElements.end()) {
						mouseLeft = true;
					}

					if (mouseLeft) {
						m_currentlyHoveredElements.erase(element);
						element->mouseLeave();

						if (m_changingState) return false; // button call changed state; abort
					}
				}
			}
		}
	}

	return false; // don't quit by default
}

void Engine::renderFrame() {
	m_gameStates.top()->drawFrame();
	SDL_RenderPresent(m_renderer);
	SDL_RenderClear(m_renderer);
}

void Engine::cleanup() {
	while (!m_gameStates.empty()) {
		m_gameStates.pop();
	}
}

SDL_Renderer* Engine::getRenderer() {
	return m_renderer;
}