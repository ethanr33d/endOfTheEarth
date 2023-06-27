// class that controls the help screen on the main menu
#pragma once

#include "GameState.h"
#include "UI/Button.h"

class HelpScreen : public GameState {
	private:
		Button backButton;
		TTF_Font* helpFont;
		SDL_Texture* helpTitle;
		SDL_Texture* helpText;

		void backHandle();
	public:
		~HelpScreen();
		HelpScreen(Engine& engine);
		virtual void drawFrame();
};