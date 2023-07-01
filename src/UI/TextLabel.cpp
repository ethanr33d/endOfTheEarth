#include "TextLabel.h"

TextLabel::TextLabel(SDL_Renderer* renderer, const std::string& text) : UIFrame(renderer),
	m_labelText(TextNode(renderer, text)) {
	
	m_labelText.show();
}

void TextLabel::setSize(int w, int h) {
	UIFrame::setSize(w, h); // default behavior
	
	SDL_Rect textRect = m_labelText.getTextBounds();

	// compute scalar so text will fit inside bounds of label
	double scalar = fmin(static_cast<double>(m_bounds.w - TEXT_PADDING * 2) / textRect.w,
		static_cast<double>(m_bounds.h - TEXT_PADDING * 2) / textRect.h);

	scalar = fmax(scalar, 0);

	m_labelText.setSize(static_cast<int>(textRect.w * scalar), static_cast<int>(textRect.h * scalar));
	setPosition(m_bounds.x, m_bounds.y); // recompute text position
}

void TextLabel::setPosition(int x, int y) {
	UIFrame::setPosition(x, y); // default behavior

	// position text in center of button
	SDL_Rect textRect = m_labelText.getBounds();
	m_labelText.setPosition((m_bounds.x + m_bounds.w / 2) - (textRect.w / 2), 
		(m_bounds.y + m_bounds.h / 2) - (textRect.h / 2));
}
void TextLabel::draw() {
	if (!m_shown) return;

	// draw background and border
	UIFrame::draw();
	m_labelText.draw();
}
