#include "GameLoading.h"

GameLoading::GameLoading(Engine& engine) : GameState(engine), 
		m_game(GameData(engine.getRenderer(), engine.getPhysicsEngine())) {
	m_game.player.setSize(100, 100);
	m_game.player.setPosition(450, 200);

	m_game.frame1.setSize(100, 100);
	m_game.frame1.setPosition(250, 250);
	m_game.frame1.setBGColor(SDL_Color{ 255, 128, 128, 255 });
	m_game.frame2.setSize(100, 50);
	m_game.frame2.setPosition(350, 25);
	m_game.frame2.setBGColor(SDL_Color{ 0, 255, 0, 255 });
	m_game.frame3.setSize(20, 40);
	m_game.frame3.setPosition(75, 300);
	m_game.frame3.setBGColor(SDL_Color{ 0, 0, 255, 255 });

	m_game.frame1.show();
	m_game.frame2.show();
	m_game.frame3.show();
	registerKeyboardListener(&m_game.player);
	engine.getPhysicsEngine().addCollidableElement(&m_game.player);
	engine.getPhysicsEngine().addCollidableElement(&m_game.frame1);
	engine.getPhysicsEngine().addCollidableElement(&m_game.frame2);
	engine.getPhysicsEngine().addCollidableElement(&m_game.frame3);
}

void GameLoading::drawFrame() {
	m_game.player.draw();
	m_game.frame1.draw();
	m_game.frame2.draw();
	m_game.frame3.draw();
	SDL_SetRenderDrawColor(m_engine.getRenderer(), 255, 255, 255, 255);
}