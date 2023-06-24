#include "Button.h"

// cleanup
Button::~Button() {
	TTF_CloseFont(font);
	SDL_DestroyTexture(textTexture);
}

void Button::createTextTexture(SDL_Renderer* renderer) {
	if (!font) {
		font = TTF_OpenFont(DEFAULT_FONT.c_str(), DEFAULT_FONT_SIZE);
	}

	if (buttonText == "") {
		buttonText = " "; // empty string not permitted in text render functions
	}
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, buttonText.c_str(), fontColor);

	if (!textSurface) {
		SDLUtils::error("Button::createTextTexture RenderTextBlend");
		return;
	}

	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	if (!textTexture) {
		SDLUtils::error("Button::createTextTexture TextureFromSurface");
		return;
	}

	SDL_SetTextureScaleMode(textTexture, SDL_ScaleModeBest); // for better text scaling
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

void Button::setMouseDownHandle(std::function<void()> func) {
	downHandler = func;
}

void Button::setMouseUpHandle(std::function<void()> func) {
	upHandler = func;
}

void Button::setHoverStartHandle(std::function<void()> func) {
	hoverStartHandler = func;
}

void Button::setHoverEndHandle(std::function<void()> func) {
	hoverEndHandler = func;
}

void Button::mouseDown() {
	clicking = true;

	if (downHandler) downHandler();
}

void Button::mouseUp() {
	clicking = false;

	if (upHandler) upHandler();
}

void Button::mouseEnter() {
	hover = true;

	if (hoverStartHandler) hoverStartHandler();
}

void Button::mouseLeave() {
	hover = false;
	clicking = false;

	if (hoverEndHandler) hoverEndHandler();
}

SDL_Rect Button::getClickBox() {
	return SDL_Rect{ x,y,w,h };
}

SDL_Rect Button::getHoverBox() {
	return SDL_Rect{ x,y,w,h };
}

void Button::draw(SDL_Renderer* renderer) {
	if (!shown) return;
	// border is not included in button size
	SDL_Rect borderRect{ x - borderSize, y - borderSize, w + 2 * borderSize, h + 2 * borderSize};
	SDL_Rect bgRect{ x, y, w, h };
	SDL_Rect textRect{ 0,0,0,0 };

	if (!textTexture) {
		createTextTexture(renderer);
	}

	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h); // get total text dimensions
	// create border
	SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	SDL_RenderFillRect(renderer, &borderRect);

	// create background
	if (clicking) {
		SDL_SetRenderDrawColor(renderer, clickColor.r, clickColor.g, clickColor.b, clickColor.a);
	}
	else if (hover) {
		SDL_SetRenderDrawColor(renderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
	}
	else {
		SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	}

	SDL_RenderFillRect(renderer, &bgRect);

	// create text
	// scalar for resizing text to fit button, *2 for both sides
	double scalar = fmin(static_cast<double>(bgRect.w - TEXT_PADDING * 2) / textRect.w, 
						 static_cast<double>(bgRect.h - TEXT_PADDING * 2) / textRect.h);
	textRect.w = static_cast<int>(textRect.w * scalar);
	textRect.h = static_cast<int>(textRect.h * scalar);
	textRect.x = (x + w / 2) - (textRect.w / 2);
	textRect.y = (y + h / 2) - (textRect.h / 2);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect); // text should only fill background
}