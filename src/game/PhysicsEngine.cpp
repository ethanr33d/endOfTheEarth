#include "PhysicsEngine.h"

SDL_Rect PhysicsEngine::getNearestValidCoords(const SDL_Rect& currentPos, const int destX, const int destY) {
	SDL_Rect destRect = currentPos; // default back to original position if no possible movement
	
	// if no change desired on axis skip checking
	

}