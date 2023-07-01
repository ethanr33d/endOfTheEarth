#include "CreditsScreen.h"

CreditsScreen::CreditsScreen(Engine& engine) : HelpScreen(engine) {
	m_helpText.setText(CREDIT_TEXT);
	m_title.setText("Credits");

	SDL_Rect titleBounds = m_title.getBounds();
	SDL_Rect textBounds = m_helpText.getBounds();

	m_title.setPosition(500 - titleBounds.w / 2, 25);
	m_helpText.setPosition(500 - textBounds.w / 2, 50 + m_title.getBounds().h);

	m_backButton.setPosition(400, m_helpText.getBounds().y + textBounds.h + 25);
}

void CreditsScreen::drawFrame() {
	HelpScreen::drawFrame();
}