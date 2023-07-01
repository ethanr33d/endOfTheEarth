#include "HelpScreen.h"

void HelpScreen::backHandle() {
	m_engine.popGameState(); // return to main menu
}

HelpScreen::HelpScreen(Engine& engine) 
	: GameState(engine), 
	m_backButton(Button(engine.getRenderer(), "Back")),
	m_title(TextNode(engine.getRenderer(), "Help")),
	m_helpText(TextNode(engine.getRenderer(), HELP_TEXT)) {

	m_title.setFontSize(64);
	
	m_helpText.setWrapped(true);
	m_helpText.setFontSize(24);

	SDL_Rect titleBounds = m_title.getBounds();
	SDL_Rect helpBounds = m_helpText.getBounds();

	m_title.setPosition(500 - titleBounds.w / 2, 25); // center horizontally
	m_helpText.setPosition(500 - helpBounds.w / 2, 50 + titleBounds.h); // center and place after title

	helpBounds = m_helpText.getBounds(); // get updated position

	m_backButton.setSize(200, 75);
	m_backButton.setPosition(400, helpBounds.y + helpBounds.h + 25); // position after help text

	m_backButton.setMouseUpHandle(std::bind(&HelpScreen::backHandle, this));

	registerClickable(&m_backButton);
	registerHoverable(&m_backButton);

	m_title.show();
	m_helpText.show();
	m_backButton.show();
}

void HelpScreen::drawFrame() {
	SDL_Renderer* renderer = m_engine.getRenderer();

	MainMenu::drawDefaultBackground(renderer);
	m_title.draw();
	m_helpText.draw();
	m_backButton.draw();
}