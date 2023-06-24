#include "MainMenu.h"

void MainMenu::playHandle() {
	std::cout << "play pressed: " << std::endl;
}

void MainMenu::helpHandle() {
	std::cout << "help pressed" << std::endl;
}

void MainMenu::creditsHandle() {
	std::cout << "credits pressed" << std::endl;
}

MainMenu::~MainMenu() {
	SDL_DestroyTexture(titleTexture);
	TTF_CloseFont(titleFont);
}

MainMenu::MainMenu(Engine& engine) : GameState(engine), playBtn(Button("Play")),
									 helpBtn(Button("Help")), creditsBtn(Button("Credits")),
									 titleTexture(nullptr), titleFont(nullptr),
									 titleTextureWidth(0), titleTextureHeight(0) {
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

	titleFont = TTF_OpenFont((SDLUtils::getResourceDirPath("fonts") + "pixelFont.ttf").c_str(), 64);

	if (!titleFont) SDLUtils::error("MainMenu::constructor TTF_OpenFont");

	SDL_Surface* surface = TTF_RenderText_Blended(titleFont, "End of the Earth", SDL_Color{ 0,0,0,255 });

	if (!surface) SDLUtils::error("MainMenu::constructor TTF_RenderText");

	titleTexture = SDL_CreateTextureFromSurface(engine.getRenderer(), surface);
	SDL_QueryTexture(titleTexture, NULL, NULL, &titleTextureWidth, &titleTextureHeight);
	SDL_FreeSurface(surface);
}

void MainMenu::drawFrame() {
	SDL_Renderer* renderer = engine.getRenderer();
	SDL_Rect skyRect{ 0,0, 1000, 355 };
	SDL_Rect grassRect{ 0,355, 1000, 30 };
	SDL_Rect dirtRect{ 0,385, 1000, 150 };
	SDL_Rect titleRect{ 500 - titleTextureWidth / 2, 25, titleTextureWidth, titleTextureHeight };
	// draw sky
	SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
	SDL_RenderFillRect(renderer, &skyRect);

	// draw grass
	SDL_SetRenderDrawColor(renderer, 124, 200, 0, 255);
	SDL_RenderFillRect(renderer, &grassRect);

	// draw dirt
	SDL_SetRenderDrawColor(renderer, 131, 101, 57, 255);
	SDL_RenderFillRect(renderer, &dirtRect);

	// draw title
	SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);

	// draw buttons
	playBtn.draw(engine.getRenderer());
	helpBtn.draw(engine.getRenderer());
	creditsBtn.draw(engine.getRenderer());
	SDL_SetRenderDrawColor(engine.getRenderer(), 255, 128, 128, 255);
}