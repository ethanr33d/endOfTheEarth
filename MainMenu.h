// Game state for the Main Menu

#pragma once

#include "GameState.h"
#include "Button.h"

class MainMenu : public GameState {
	private:
		Button playBtn;
		Button helpBtn;
		Button creditsBtn;
		SDL_Texture* titleTexture;
		int titleTextureWidth;
		int titleTextureHeight;
		TTF_Font* titleFont;

		void playHandle();
		void helpHandle();
		void creditsHandle();
	public:
		~MainMenu();
		MainMenu(Engine& engine);
		virtual void drawFrame();
};

//TODO:
//make base menu
//help screen
//credits screen
//character movement