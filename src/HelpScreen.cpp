#include "HelpScreen.h"

void HelpScreen::backHandle() {
	engine.popGameState(); // return to main menu
}

HelpScreen::HelpScreen(Engine& engine) : GameState(engine), backButton(Button("Back")),
		title(TextNode("Help")), helpText(TextNode(HELP_TEXT)) {
	title.setFontSize(64);
	
	helpText.setWrapped(true);
	helpText.setFontSize(24);

	SDL_Rect titleBounds = title.getBounds();
	SDL_Rect helpBounds = helpText.getBounds();

	title.setPosition(500 - titleBounds.w / 2, 25); // center horizontally
	helpText.setPosition(500 - helpBounds.w / 2, 50 + titleBounds.h); // center and place after title

	helpBounds = helpText.getBounds(); // get updated position

	backButton.setSize(200, 75);
	backButton.setPosition(400, helpBounds.y + helpBounds.h + 25); // position after help text

	backButton.setMouseUpHandle(std::bind(&HelpScreen::backHandle, this));

	registerClickable(&backButton);
	registerHoverable(&backButton);

	title.show();
	helpText.show();
	backButton.show();
}

void HelpScreen::drawFrame() {
	SDL_Renderer* renderer = engine.getRenderer();

	MainMenu::drawDefaultBackground(renderer);
	title.draw(renderer);
	helpText.draw(renderer);
	backButton.draw(renderer);
}