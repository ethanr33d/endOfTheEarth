#include "Button.h"

void Button::setMouseDownHandle(const std::function<void()>& func) {
	downHandler = func;
}

void Button::setMouseUpHandle(const std::function<void()>& func) {
	upHandler = func;
}

void Button::setHoverStartHandle(const std::function<void()>& func) {
	hoverStartHandler = func;
}

void Button::setHoverEndHandle(const std::function<void()>& func) {
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

	// set correct background color
	if (clicking) {
		bgColor = clickColor;
	}
	else if (hover) {
		bgColor = hoverColor;
	}
	else {
		bgColor = idleColor;
	}

	// button is a text label
	TextLabel::draw(renderer);
}