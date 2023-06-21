// Interface that defines required functions for game states
#pragma once

#include "SDL2/SDL.h"
#include "Engine.h"

class IGameState {
	private:

	protected:
		Engine& engine;
	public:
		IGameState(Engine& eng) : engine(eng) {};
		virtual void drawFrame() = 0;
};