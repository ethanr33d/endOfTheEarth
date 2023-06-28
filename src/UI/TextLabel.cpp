#include "TextLabel.h"

void TextLabel::draw(SDL_Renderer* renderer) {
	// draw background and border
	UIFrame::draw(renderer);

	SDL_Rect textRect = labelText.getBounds();

	// scalar for resizing text to fit button, *2 for both sides
	// essentially looking for largest scalar that will still fit in box
	double scalar = fmin(static_cast<double>(w - TEXT_PADDING * 2) / textRect.w,
		static_cast<double>(h - TEXT_PADDING * 2) / textRect.h);

	labelText.setSize(static_cast<int>(textRect.w * scalar), static_cast<int>(textRect.h * scalar));
	labelText.setPosition((x + w / 2) - (textRect.w / 2), (y + h / 2) - (textRect.h / 2));
	
	labelText.draw(renderer);
}
