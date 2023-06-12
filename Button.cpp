#include "Button.h"

// cleanup
Button::~Button() {
	TTF_CloseFont(font);
	SDL_DestroyTexture(textTexture);
}

void Button::createTextTexture(SDL_Renderer* renderer) {
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, buttonText.c_str(), fontColor);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_FreeSurface(textSurface);
}

void Button::setPosition(int xPos, int yPos) {
	x = xPos;
	y = yPos;
}

void Button::setSize(int width, int height) {
	w = width;
	h = height;
}

void Button::setBorder(SDL_Color color, int size) {
	borderColor = color;
	borderSize = size;
}

void Button::setMouseDownHandle(void (*func) ()) {
	upHandler = func;
}

void Button::setMouseUpHandle(void (*func) ()) {
	downHandler = func;
}

void Button::mouseDown() {
	downHandler();
}

void Button::mouseUp() {
	upHandler();
}

void Button::render(SDL_Renderer* renderer) {
	if (!shown) return;
	// border is not included in button size
	SDL_Rect borderRect{ x - borderSize, y - borderSize, w + 2 * borderSize, h + 2 * borderSize};
	SDL_Rect bgRect{ x, y, w, h };
	SDL_Rect textRect{ 0,0,0,0 };

	if (!textTexture) createTextTexture(renderer);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h); // get total text dimensions
	// create border
	SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	SDL_RenderFillRect(renderer, &borderRect);

	// create background
	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_RenderFillRect(renderer, &bgRect);

	// create text
	textRect.x = (x + w / 2) - (textRect.w / 2);
	textRect.y = (y + h / 2) - (textRect.h / 2);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect); // text should only fill background
}