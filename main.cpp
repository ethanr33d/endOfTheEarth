#include <iostream>
#include  "SDL2/SDL.h"
#include "SDLUtils.h"
#include "Button.h"
#include "Engine.h"
#include "MainMenu.h"

// Constants
const char* GAME_NAME = "End of the Earth";

int main(int, char**) {
	Engine gameEngine;

	if (!gameEngine.initializeComponents(GAME_NAME)) {
		gameEngine.cleanup();
		return 1;
	}

	gameEngine.pushGameState(MainMenu(gameEngine));

	bool readyToQuit = false;

	while (!readyToQuit) {
		readyToQuit = gameEngine.handleEvents(); 
		gameEngine.renderFrame();
	}

	//cleanup
	gameEngine.cleanup();
	return 0;
}