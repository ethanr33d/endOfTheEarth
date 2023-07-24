#include "GameLoading.h"
#include <cmath>
GameLoading::GameLoading(Engine& engine) : GameState(engine), 
		m_game(GameData(engine.getRenderer())) {
	PhysicalWorld* simulaton = engine.getPhysicsSimulation();
	Camera* camera = engine.getCamera();

	m_game.player.setSize(Vector2{ 96, 96 });
	m_game.player.setPosition(Vector2{ 300, -100 });
	
	srand(SDL_GetTicks());
	for (int i = 0; i < 6; i++) {
		Brick* newBrick = new Brick(engine.getRenderer());

		newBrick->setSize(Vector2{ 50, 50});
		newBrick->setPosition(Vector2{ 75 + i * 150, 50 + i * 50});
		newBrick->setColor(SDLUtils::getRandomColor());
		newBrick->setAnchored(true);

		simulaton->addElement(newBrick);
		m_game.brickList.push_back(newBrick);
	}

	Brick* ice = new Brick(engine.getRenderer());
	Brick* mud = new Brick(engine.getRenderer());
	Brick* grass = new Brick(engine.getRenderer());

	ice->setSize(Vector2{500, 500});
	ice->setPosition(Vector2{0,400});
	ice->setColor(SDL_Color{ 52, 168, 235, 255 });
	ice->setFrictionConstant(0.1);
	ice->setAnchored(true);

	mud->setSize(Vector2{500, 500});
	mud->setPosition(Vector2{-500,400});
	mud->setColor(SDL_Color{ 100, 100, 100, 255 });
	mud->setFrictionConstant(1);
	mud->setAnchored(true);

	grass->setSize(Vector2{500, 500});
	grass->setPosition(Vector2{500,400});
	grass->setColor(SDL_Color{ 87, 189, 40, 255 });
	grass->setAnchored(true);

	simulaton->addElement(ice);
	m_game.brickList.push_back(ice);
	simulaton->addElement(mud);
	m_game.brickList.push_back(mud);
	simulaton->addElement(grass);
	m_game.brickList.push_back(grass);
	registerKeyboardListener(&m_game.player);
	simulaton->addElement(&m_game.player);

	camera->setSubject(&m_game.player);
	camera->setMode(CENTER_SUBJECT);

}

void GameLoading::drawFrame() {
	SDL_SetRenderDrawBlendMode(m_engine.getRenderer(), SDL_BLENDMODE_NONE);
	
	for (Brick* element : m_game.brickList) {
		element->draw();
	}

	m_game.player.draw();
	SDL_SetRenderDrawColor(m_engine.getRenderer(), 255, 255, 255, 255);
}