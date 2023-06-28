// Game state for the Main Menu

#pragma once

#include "GameState.h"
#include "UI/Button.h"
#include "SDLUtils.h"


class MainMenu : public GameState {
	private:
		inline static const std::string TITLE_FONT = SDLUtils::getResourceDirPath("fonts") + "pixelFont.ttf";
		inline static const std::string GAME_NAME = "End of the Earth";
		Button playBtn;
		Button helpBtn;
		Button creditsBtn;
		TextNode title;

		void playHandle();
		void helpHandle();
		void creditsHandle();
	public:
		MainMenu(Engine& engine);
		virtual void drawFrame();

		// draw default background. static so other menus and screens can use it
		static void drawDefaultBackground(SDL_Renderer* renderer);
};