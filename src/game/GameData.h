// Game Data struct for data related to a round of the game
// Gets passed between game states
#pragma once

#include <vector>
#include "game/Player.h"
#include "game/PhysicsEngine.h"
#include "game/Brick.h"

struct GameData {
	Player player;
	std::vector<Brick*> brickList;
	// other useful state information here

	GameData(SDL_Renderer* renderer, PhysicsEngine& physicsEngine)
		: player(Player(renderer)) {};
};