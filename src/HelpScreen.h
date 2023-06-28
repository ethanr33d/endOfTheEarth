// class that controls the help screen on the main menu
#pragma once

#include "GameState.h"
#include "MainMenu.h"
#include "UI/Button.h"

class HelpScreen : public GameState {
	private:
		inline static const std::string HELP_TEXT = "This is a placeholder \n"
			"super cool help text goes here \n"
			"and i do mean super cool \n"
			"this concludes the tutorial \n"
			"go test something else now \n";

		Button backButton;
		TextNode title;
		TextNode helpText;

		void backHandle();
	public:
		HelpScreen(Engine& engine);
		virtual void drawFrame();
};