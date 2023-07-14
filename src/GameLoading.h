#pragma once

#include "GameState.h"
#include "game/GameData.h"
#include "game/Vector2.h"

class GameLoading : public GameState {
	private:
		GameData m_game;
	public:

	GameLoading(Engine& engine);
	virtual void drawFrame();
};