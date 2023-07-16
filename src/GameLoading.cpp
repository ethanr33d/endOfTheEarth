#include "GameLoading.h"
#include <cmath>
GameLoading::GameLoading(Engine& engine) : GameState(engine), 
		m_game(GameData(engine.getRenderer(), engine.getPhysicsEngine())) {
	m_game.player.setSize(Vector2{ 100, 100 });
	m_game.player.setPosition(Vector2{ 450, 200 });
	
	srand(SDL_GetTicks());
	for (int i = 0; i < 6; i++) {
		Brick* newBrick = new Brick(engine.getRenderer());

		newBrick->setSize(Vector2{ 50, 50});
		newBrick->setPosition(Vector2{ 75 + i * 150, 50 + i * 50});
		newBrick->setColor(SDLUtils::getRandomColor());
		newBrick->setAnchored(true);

		engine.getPhysicsEngine().addPhysicsElement(newBrick);
		m_game.brickList.push_back(newBrick);
	}

	Brick* ice = new Brick(engine.getRenderer());
	Brick* mud = new Brick(engine.getRenderer());
	Brick* grass = new Brick(engine.getRenderer());

	ice->setSize(Vector2{350, 100});
	ice->setPosition(Vector2{350,400});
	ice->setColor(SDL_Color{ 52, 168, 235, 255 });
	ice->setFrictionConstant(0.05);
	ice->setAnchored(true);

	mud->setSize(Vector2{350, 100});
	mud->setPosition(Vector2{0,400});
	mud->setColor(SDL_Color{ 120, 65, 35, 255 });
	mud->setFrictionConstant(1);
	mud->setAnchored(true);

	grass->setSize(Vector2{350, 100});
	grass->setPosition(Vector2{700,400});
	grass->setColor(SDL_Color{ 87, 189, 40, 255 });
	grass->setAnchored(true);

	engine.getPhysicsEngine().addPhysicsElement(ice);
	m_game.brickList.push_back(ice);
	engine.getPhysicsEngine().addPhysicsElement(mud);
	m_game.brickList.push_back(mud);
	engine.getPhysicsEngine().addPhysicsElement(grass);
	m_game.brickList.push_back(grass);
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