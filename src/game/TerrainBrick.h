// creates a brick with appropriately blended terrain

#pragma once

#include "PhysicsElement.h"

struct TerrainSpriteClips {
	SDL_Rect top1;
	SDL_Rect top2;
	SDL_Rect top3;
	SDL_Rect island;
	SDL_Rect underground1;
	SDL_Rect underground2;
	SDL_Rect underground3;
	SDL_Rect deepUnderground;
};

class TerrainBrick : PhysicsElement {
	private:
		
		
	public:
		TerrainBrick(SDL_Texture* tileset);
};