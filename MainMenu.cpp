#include "MainMenu.h"
void printTest() {
	std::cout << "test" << std::endl;
}

MainMenu::MainMenu(Engine& engine) : GameState(engine) {
	// test case
	button1 = Button("Menu");
	button1.setSize(200, 100);
	button1.setPosition(450, 250);
	button1.show();
	button1.setMouseUpHandle(printTest);

	button2 = Button("Menu");
	button2.setSize(400, 200);
	button2.setPosition(5, 5);
	button2.show();
	button2.setMouseUpHandle(printTest);

	button3 = Button("Menu");
	button3.setSize(50, 100);
	button3.setPosition(700, 350);
	button3.show();
	button3.setMouseUpHandle(printTest);

	button4 = Button("Menu");
	button4.setSize(200, 200);
	button4.setPosition(50, 250);
	button4.show();
	button4.setMouseUpHandle(printTest);

	registerClickable(&button1);
	registerClickable(&button2);
	registerClickable(&button3);
	registerClickable(&button4);
	registerHoverable(&button1);
	registerHoverable(&button2);
	registerHoverable(&button3);
	registerHoverable(&button4);

}

void MainMenu::drawFrame() {
	button1.draw(engine.getRenderer());
	button2.draw(engine.getRenderer());
	button3.draw(engine.getRenderer());
	button4.draw(engine.getRenderer());
	SDL_SetRenderDrawColor(engine.getRenderer(), 255, 128, 128, 255);
}