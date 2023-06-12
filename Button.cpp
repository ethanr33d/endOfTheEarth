#include "Button.h"

void Button::SetPosition(int x, int y) {
	xPos = x;
	yPos = y;
}

void Button::SetBorder(SDL_Color color, int size) {
	borderColor = color;
	borderSize = size;
}

void Button::OnClick(void* func) {
	handler = func;
}