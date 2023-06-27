#include "UIFrame.h"

void UIFrame::setBorderColor(const SDL_Color& color) {
	borderColor = color;
}

void UIFrame::setBorderSize(const int size) {
	borderSize = size;
}

void UIFrame::setBGColor(const SDL_Color& color) {
	bgColor = color;
}

void UIFrame::draw(SDL_Renderer* renderer) {
	if (!shown) return;
	
	//border not included in width and height
	SDL_Rect borderRect{ x - borderSize, y - borderSize, w + 2 * borderSize, h + 2 * borderSize };
	SDL_Rect bgRect{ x, y, w, h };

	SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	SDL_RenderFillRect(renderer, &borderRect);

	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_RenderFillRect(renderer, &bgRect);
}
