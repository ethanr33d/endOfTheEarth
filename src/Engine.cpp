#include "Engine.h"
#include "GameState.h"
#include "MainMenu.h"
#include "HelpScreen.h"
#include "CreditsScreen.h"
#include "GameLoading.h"
// private member methods
void Engine::reportFinishedFrame(int time) {
	if (m_frameFinishTimes.size() >= FPS_N_AVERAGE) {
		m_frameFinishTimes.pop();
	}

	m_frameFinishTimes.push(time);
}

void Engine::renderFPS() {
	if (m_frameFinishTimes.empty()) {
		m_fpsCounter->draw(); // no frames to calculate yet
		return;
	}

	// current time - first completion time in batch
	int totFrameTime = SDL_GetTicks() - m_frameFinishTimes.front();

	if (totFrameTime > 0) {
		double fps = m_frameFinishTimes.size() / (static_cast<double>(totFrameTime) / 1000); // convert ms to s
		m_fpsCounter->setText("FPS: " +  std::to_string(fps));
	}
	else {
		m_fpsCounter->setText("FPS: inf");
	}

	m_fpsCounter->draw();
}

void Engine::transitionGameState(GameState* state) {
	// set tracked elements to new state
	m_clickableElements = state->getClickableElements();
	m_hoverableElements = state->getHoverableElements();
	m_keyboardListeners = state->getKeyboardListeners();
	m_currentlyHoveredElements = state->getCurrentlyHoveredElements();

	// reset mouse state since mouse state might have changed between states
	// e.x: mouse may no longer be hovering over an element it was hovering over
	// prior to a state change
	SDL_Event mouseResetEvent{};

	int mouseX{ 0 }, mouseY{ 0 };
	SDL_GetMouseState(&mouseX, &mouseY);

	mouseResetEvent.type = SDL_MOUSEMOTION;
	mouseResetEvent.motion.x = mouseX;
	mouseResetEvent.motion.y = mouseY;

	SDL_PushEvent(&mouseResetEvent);
}

// public methods
Engine::~Engine() {
	// clean state memory
	while (!m_gameStates.empty()) {
		GameState* stateToRemove = m_gameStates.top();
		m_gameStates.pop();

		delete stateToRemove;
	}

	delete m_fpsCounter;
	delete m_physicsEngine;
	delete m_camera;
	delete m_physicsSimulation;

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

	m_fpsCounter = new TextNode(m_renderer, "FPS:", 16); // initialize fpsCounter
	m_fpsCounter->show();

	m_physicsSimulation = new PhysicalWorld();
	m_physicsEngine = new PhysicsEngine(*m_physicsSimulation);
	m_camera = new Camera(*m_physicsSimulation);
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
		case CREDITS_SCREEN:
			newState = new CreditsScreen(*this);
			break;
		case GAME_LOADING:
			newState = new GameLoading(*this);
			break;
	}

	m_gameStates.push(newState);
	m_changingState = true;

	transitionGameState(newState);
}

void Engine::popGameState() {
	if (m_gameStates.size() <= 1) std::cerr << "No game state to pop back to" << std::endl;

	GameState* deadState = m_gameStates.top();

	m_gameStates.pop();
	m_changingState = true;
	delete deadState; // release memory

	transitionGameState(m_gameStates.top());
}

bool Engine::handleEvents() {
	SDL_Event event{};
	m_changingState = false; // fresh event loop

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
			{
				return true;
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			{
				for (IClickable* element : *m_clickableElements) {
					SDL_Rect elementBox = element->getClickBox();
					bool contained = pointContainedInBox(elementBox, event.button.x, event.button.y);

					if (contained) {
						if (event.type == SDL_MOUSEBUTTONDOWN) element->mouseDown();
						if (event.type == SDL_MOUSEBUTTONUP) element->mouseUp();

						if (m_changingState) break; // button press resulted in state change; abort
					}
				}
				break;
			}
			case SDL_MOUSEMOTION:
			{
				// hover events (pseudo mouseEnter & mouseLeave events)
				for (IHoverable* element : *m_hoverableElements) {
					SDL_Rect elementBox = element->getHoverBox();
					bool contained = pointContainedInBox(elementBox, event.motion.x, event.motion.y);

					if (contained) { // check if we need to fire mouseEnter
						bool mouseEntered = true;

						// check if mouse already hovering over element
						if (m_currentlyHoveredElements->find(element) != m_currentlyHoveredElements->end()) {
							mouseEntered = false; // mouseEntered event has already fired	
						}
					
						if (mouseEntered) { // if mouseEntered has not already fired
							m_currentlyHoveredElements->insert(element);
							element->mouseEnter();
							if (m_changingState) break; // button call changed state; abort
						}
					
					}
					else { // check if we need to fire mouseLeave
						bool mouseLeft = false;

						// check to see if we are tracking element for a leave event
						if (m_currentlyHoveredElements->find(element) != m_currentlyHoveredElements->end()) {
							mouseLeft = true;
						}

						if (mouseLeft) {
							m_currentlyHoveredElements->erase(element);
							element->mouseLeave();

							if (m_changingState) break; // button call changed state; abort
						}
					}
				}
				break;
			}
			case SDL_KEYDOWN:
			{
				// event may fire more than once by OS when key is held down
				// this loop prevents more than one keyDown event from firing on an element
				bool abortEvent = false;
				for (SDL_Keycode key : m_keysDown) {
					if (event.key.keysym.sym == key) {
						abortEvent = true; // key already marked down
						break;
					}
				}
				if (abortEvent) break;
				[[fallthrough]];
			}
			case SDL_KEYUP:
			{
				// forward key event to element for processing
				for (IKeyboardListener* element : *m_keyboardListeners) {
					if (event.type == SDL_KEYDOWN) {
						element->keyDown(event.key.keysym.sym);
						m_keysDown.insert(event.key.keysym.sym);
					}
					else {
						element->keyUp(event.key.keysym.sym);
						m_keysDown.erase(event.key.keysym.sym);
					}

				}
				break;
			}
		}
	}

	return false; // don't quit by default
}

void Engine::physicsStep() {
	m_physicsSimulation->firePrePhysicsEvent();
	m_physicsEngine->step();
	m_physicsSimulation->firePostPhysicsEvent();
	m_camera->step();
}

void Engine::renderFrame() {
	m_gameStates.top()->drawFrame();
	renderFPS(); // draw FPS counter
	SDL_RenderPresent(m_renderer);
	SDL_RenderClear(m_renderer);
	reportFinishedFrame(SDL_GetTicks());
}

void Engine::cleanup() {
	while (!m_gameStates.empty()) {
		m_gameStates.pop();
	}
}

SDL_Renderer* Engine::getRenderer() {
	return m_renderer;
}

PhysicalWorld* Engine::getPhysicsSimulation() {
	return m_physicsSimulation;
}

Camera* Engine::getCamera() {
	return m_camera;
}