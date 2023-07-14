#include "GameLoading.h"

GameLoading::GameLoading(Engine& engine) : GameState(engine), 
		m_game(GameData(engine.getRenderer(), engine.getPhysicsEngine())) {
	m_game.player.setSize(Vector2{ 100, 100 });
	m_game.player.setPosition(Vector2{ 450, 200 });

	m_game.brick1.setSize(Vector2 { 100, 100});
	m_game.brick1.setPosition(Vector2 { 250, 250});
	m_game.brick1.setColor(SDL_Color{ 255, 128, 128, 255 });
	m_game.brick1.setAnchored(true);

	m_game.brick2.setSize(Vector2 {100, 50});
	m_game.brick2.setPosition(Vector2 {350, 25});
	m_game.brick2.setColor(SDL_Color{ 0, 255, 0, 255 });
	m_game.brick2.setAnchored(true);

	m_game.brick3.setSize(Vector2 {20, 40});
	m_game.brick3.setPosition(Vector2 {75, 300});
	m_game.brick3.setColor(SDL_Color{ 0, 0, 255, 255 });
	m_game.brick3.setAnchored(true);

	registerKeyboardListener(&m_game.player);
	engine.getPhysicsEngine().addCollidableElement(&m_game.player);
	engine.getPhysicsEngine().addCollidableElement(&m_game.brick1);
	engine.getPhysicsEngine().addCollidableElement(&m_game.brick2);
	engine.getPhysicsEngine().addCollidableElement(&m_game.brick3);
}

void GameLoading::drawFrame() {
	SDL_SetRenderDrawBlendMode(m_engine.getRenderer(), SDL_BLENDMODE_NONE);
	m_game.brick1.draw();
	m_game.brick2.draw();
	m_game.brick3.draw();

	m_game.player.draw();
	SDL_SetRenderDrawColor(m_engine.getRenderer(), 255, 255, 255, 255);
}