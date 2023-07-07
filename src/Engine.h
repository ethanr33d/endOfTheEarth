// Responsible for managing high level components and handling events
#pragma once

#include <string>
#include <set>
#include <stack>
#include <queue>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDLUtils.h"
#include "UI/IClickable.h"
#include "UI/IHoverable.h"
#include "IKeyboardListener.h"
#include "game/PhysicsEngine.h"

class GameState; // forward declaration for circular dependency
class TextNode;

enum GAME_STATE{MAIN_MENU, HELP_SCREEN, CREDITS_SCREEN, GAME_LOADING};

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
		inline static const int RENDERER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

		// Engine constants
		inline static const int FPS_N_AVERAGE = 100; // average fps calculated over this many frames

		/* private member variables */
		//Engine Stats
		TextNode* m_fpsCounter; // initialized in initializeComponents
		std::queue<int> m_frameFinishTimes; // queue of the finish time of recent fps_n_avg frames
		
		// Engine member variables
		std::set<IClickable*>* m_clickableElements; // elements engine checks for events
		std::set<IHoverable*>* m_hoverableElements; 
		std::set<IKeyboardListener*>* m_keyboardListeners;
		std::set<IHoverable*>* m_currentlyHoveredElements;

		std::stack<GameState*> m_gameStates;
		SDL_Window* m_mainWindow;
		SDL_Renderer* m_renderer;
		PhysicsEngine m_physicsEngine;
		
		// Engine state variables
		bool m_changingState; // used to invalidate event loop after state changes
		std::set<SDL_Keycode> m_keysDown;

		/* private member methods */
		void reportFinishedFrame(int time); 
		void renderFPS();

		void transitionGameState(GameState* state); // internal transition cleanup

		// returns whether the given x,y is contained within the target rectangle.
		// the edge is included
		bool pointContainedInBox(const SDL_Rect& target, int queryX, int queryY);

	public:
		// where components are destroyed
		~Engine();

		Engine() : m_fpsCounter{ nullptr }, m_clickableElements{ nullptr }, m_hoverableElements{ nullptr },
			m_keyboardListeners{ nullptr }, m_currentlyHoveredElements{ nullptr },
			m_mainWindow { nullptr }, m_renderer{ nullptr }, m_changingState{ false } {};
		/* Init/Game loop functions */


		// Initializes the main window and rendering context we will use throughout game
		// window and renderer reference parameters updated with new components
		// returns true on success false on failure
		bool initializeComponents(const std::string& appName = "");

		// change the games current state. Must use this before starting engine to set initial state
		void pushGameState(GAME_STATE state);

		// pop game state from stack and return to previous state. Errors if there would be no state
		// to go back to
		void popGameState();

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
		PhysicsEngine& getPhysicsEngine();
};