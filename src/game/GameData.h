// Game Data struct for data related to a round of the game
// Gets passed between game states
#pragma once

#include "game/Player.h"
#include "game/PhysicsEngine.h"
#include "UI/UIFrame.h"

struct GameData {
	Player player;
	UIFrame frame1;
	UIFrame frame2;
	UIFrame frame3;
	// other useful state information here

	GameData(SDL_Renderer* renderer, PhysicsEngine& physicsEngine)
		: player(Player(renderer, physicsEngine)), frame1(renderer), frame2(renderer), frame3(renderer) {};
};