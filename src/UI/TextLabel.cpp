#include "TextLabel.h"

TextLabel::TextLabel(const std::string& text) : m_labelText(TextNode(text)) {
	SDL_Rect textRect = m_labelText.getBounds();

	// scalar for resizing text to fit button, *2 for both sides
	// essentially looking for largest scalar that will still fit in box
	double scalar = fmin(static_cast<double>(m_w - TEXT_PADDING * 2) / textRect.w,
		static_cast<double>(m_h - TEXT_PADDING * 2) / textRect.h);

	m_labelText.setSize(static_cast<int>(textRect.w * scalar), static_cast<int>(textRect.h * scalar));
	textRect = m_labelText.getBounds(); // get updated bounds

	m_labelText.setPosition((m_x + m_w / 2) - (textRect.w / 2), (m_y + m_h / 2) - (textRect.h / 2));
	m_labelText.show();
}

void TextLabel::draw(SDL_Renderer* renderer) {
	// draw background and border
	UIFrame::draw(renderer);
	m_labelText.draw(renderer);
}
