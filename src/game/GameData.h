// Game Data struct for data related to a round of the game
// Gets passed between game states
#pragma once

#include "game/Player.h"
#include "game/PhysicsEngine.h"
#include "game/Brick.h"

struct GameData {
	Player player;
	Brick brick1;
	Brick brick2;
	Brick brick3;
	// other useful state information here

	GameData(SDL_Renderer* renderer, PhysicsEngine& physicsEngine)
		: player(Player(renderer)), brick1(renderer), brick2(renderer), brick3(renderer) {};
};