#include "HelpScreen.h"

void HelpScreen::backHandle() {
	
}

HelpScreen::~HelpScreen() {

}

HelpScreen::HelpScreen(Engine& engine) : GameState(engine), backButton(Button("Back")),
										helpFont(nullptr), helpTitle(nullptr), helpText(nullptr) {

}

void HelpScreen::drawFrame() {

}