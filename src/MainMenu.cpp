#include "MainMenu.h"

void MainMenu::playHandle() {
	std::cout << "play pressed: " << std::endl;
}

void MainMenu::helpHandle() {
	m_engine.pushGameState(HELP_SCREEN);
}

void MainMenu::creditsHandle() {
	std::cout << "credits pressed" << std::endl;
}

MainMenu::MainMenu(Engine& engine) 
	: GameState(engine), 
	m_playBtn(Button(engine.getRenderer(), "Play")),
	m_helpBtn(Button(engine.getRenderer(), "Help")),
	m_creditsBtn(Button(engine.getRenderer(), "Credits")),
	m_title(TextNode(engine.getRenderer(), GAME_NAME)) {
	// draw title
	m_title.setFont(TITLE_FONT, 64);
	SDL_Rect titleBounds = m_title.getBounds();

	m_title.setPosition(500 - titleBounds.w / 2, 25); // center horizontally
	m_title.show();
	// draw buttons
	m_playBtn.setSize(200, 75);
	m_helpBtn.setSize(200, 75);
	m_creditsBtn.setSize(200, 75);

	m_playBtn.setPosition(400, 155);
	m_helpBtn.setPosition(400, 265);
	m_creditsBtn.setPosition(400, 375);

	m_playBtn.setMouseUpHandle(std::bind(&MainMenu::playHandle, this));
	m_helpBtn.setMouseUpHandle(std::bind(&MainMenu::helpHandle, this));
	m_creditsBtn.setMouseUpHandle(std::bind(&MainMenu::creditsHandle, this));

	m_playBtn.show();
	m_helpBtn.show();
	m_creditsBtn.show();

	registerClickable(&m_playBtn);
	registerClickable(&m_helpBtn);
	registerClickable(&m_creditsBtn);
	registerHoverable(&m_playBtn);
	registerHoverable(&m_helpBtn);
	registerHoverable(&m_creditsBtn);
}

void MainMenu::drawFrame() {
	SDL_Renderer* renderer = m_engine.getRenderer();
	
	// draw default background
	drawDefaultBackground(renderer);

	// draw title
	m_title.draw();

	// draw buttons
	m_playBtn.draw();
	m_helpBtn.draw();
	m_creditsBtn.draw();
}

void MainMenu::drawDefaultBackground(SDL_Renderer* renderer) {
	SDL_Rect skyRect{ 0,0, 1000, 355 };
	SDL_Rect grassRect{ 0,355, 1000, 30 };
	SDL_Rect dirtRect{ 0,385, 1000, 150 };

	// draw sky
	SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
	SDL_RenderFillRect(renderer, &skyRect);

	// draw grass
	SDL_SetRenderDrawColor(renderer, 124, 200, 0, 255);
	SDL_RenderFillRect(renderer, &grassRect);

	// draw dirt
	SDL_SetRenderDrawColor(renderer, 131, 101, 57, 255);
	SDL_RenderFillRect(renderer, &dirtRect);
}