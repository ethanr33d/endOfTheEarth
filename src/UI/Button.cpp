#include "Button.h"

void Button::setMouseDownHandle(const std::function<void()>& func) {
	m_downHandler = func;
}

void Button::setMouseUpHandle(const std::function<void()>& func) {
	m_upHandler = func;
}

void Button::setHoverStartHandle(const std::function<void()>& func) {
	m_hoverStartHandler = func;
}

void Button::setHoverEndHandle(const std::function<void()>& func) {
	m_hoverEndHandler = func;
}

void Button::mouseDown() {
	m_clicking = true;

	if (m_downHandler) m_downHandler();
}

void Button::mouseUp() {
	m_clicking = false;

	if (m_upHandler) m_upHandler();
}

void Button::mouseEnter() {
	m_hover = true;

	if (m_hoverStartHandler) m_hoverStartHandler();
}

void Button::mouseLeave() {
	m_hover = false;
	m_clicking = false;

	if (m_hoverEndHandler) m_hoverEndHandler();
}

SDL_Rect Button::getClickBox() {
	return m_bounds;
}

SDL_Rect Button::getHoverBox() {
	return m_bounds;
}

void Button::draw() {
	if (!m_shown) return;

	// set correct background color
	if (m_clicking) {
		m_bgColor = m_clickColor;
	}
	else if (m_hover) {
		m_bgColor = m_hoverColor;
	}
	else {
		m_bgColor = m_idleColor;
	}

	// button is a text label
	TextLabel::draw();
}