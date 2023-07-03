#include "GameLoading.h"

GameLoading::GameLoading(Engine& engine) : GameState(engine), m_game(GameData(engine.getRenderer())) {
	m_game.player.setSize(100, 100);
	m_game.player.setPosition(450, 200);
	registerKeyboardListener(&m_game.player);
}

void GameLoading::drawFrame() {
	m_game.player.draw();
}