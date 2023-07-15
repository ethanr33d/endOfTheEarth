#include "GameLoading.h"
#include <cmath>
GameLoading::GameLoading(Engine& engine) : GameState(engine), 
		m_game(GameData(engine.getRenderer(), engine.getPhysicsEngine())) {
	m_game.player.setSize(Vector2{ 100, 100 });
	m_game.player.setPosition(Vector2{ 450, 200 });
	
	srand(SDL_GetTicks());
	for (int i = 0; i < 25; i++) {
		Brick* newBrick = new Brick(engine.getRenderer());

		newBrick->setSize(Vector2{ rand() % 100 + 1, rand() % 100 + 1});
		newBrick->setPosition(Vector2{ rand() % 901, rand() % 401 });
		newBrick->setColor(SDLUtils::getRandomColor());
		newBrick->setAnchored(true);

		engine.getPhysicsEngine().addPhysicsElement(newBrick);
		m_game.brickList.push_back(newBrick);
	}

	registerKeyboardListener(&m_game.player);
	engine.getPhysicsEngine().addPhysicsElement(&m_game.player);

}

void GameLoading::drawFrame() {
	SDL_SetRenderDrawBlendMode(m_engine.getRenderer(), SDL_BLENDMODE_NONE);
	
	for (Brick* element : m_game.brickList) {
		element->draw();
	}

	m_game.player.draw();
	SDL_SetRenderDrawColor(m_engine.getRenderer(), 255, 255, 255, 255);
}