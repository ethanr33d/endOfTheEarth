// Game Data struct for data related to a round of the game
// Gets passed between game states
#pragma once

#include "game/Player.h"

struct GameData {
	Player player;
	// other useful state information here

	GameData(SDL_Renderer* renderer) : player(Player(renderer)) {};
};