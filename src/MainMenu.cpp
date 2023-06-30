#include "MainMenu.h"

void MainMenu::playHandle() {
	std::cout << "play pressed: " << std::endl;
}

void MainMenu::helpHandle() {
	engine.pushGameState(HELP_SCREEN);
}

void MainMenu::creditsHandle() {
	std::cout << "credits pressed" << std::endl;
}

MainMenu::MainMenu(Engine& engine) : GameState(engine), playBtn(Button("Play")),
	helpBtn(Button("Help")), creditsBtn(Button("Credits")), title(TextNode(GAME_NAME)) {
	// draw title
	title.setFont(TITLE_FONT, 64);
	SDL_Rect titleBounds = title.getBounds();

	title.setPosition(500 - titleBounds.w / 2, 25); // center horizontally
	title.show();
	// draw buttons
	playBtn.setSize(200, 75);
	helpBtn.setSize(200, 75);
	creditsBtn.setSize(200, 75);

	playBtn.setPosition(400, 155);
	helpBtn.setPosition(400, 265);
	creditsBtn.setPosition(400, 375);

	playBtn.setMouseUpHandle(std::bind(&MainMenu::playHandle, this));
	helpBtn.setMouseUpHandle(std::bind(&MainMenu::helpHandle, this));
	creditsBtn.setMouseUpHandle(std::bind(&MainMenu::creditsHandle, this));

	playBtn.show();
	helpBtn.show();
	creditsBtn.show();

	registerClickable(&playBtn);
	registerClickable(&helpBtn);
	registerClickable(&creditsBtn);
	registerHoverable(&playBtn);
	registerHoverable(&helpBtn);
	registerHoverable(&creditsBtn);
}

void MainMenu::drawFrame() {
	SDL_Renderer* renderer = engine.getRenderer();
	
	// draw default background
	drawDefaultBackground(renderer);

	// draw title
	title.draw(renderer);

	// draw buttons
	playBtn.draw(engine.getRenderer());
	helpBtn.draw(engine.getRenderer());
	creditsBtn.draw(engine.getRenderer());
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