#pragma once

#include "GameState.h"
#include "game/GameData.h"

class GameLoading : public GameState {
	private:
		GameData m_game;
	public:

	GameLoading(Engine& engine);
	virtual void drawFrame();
};