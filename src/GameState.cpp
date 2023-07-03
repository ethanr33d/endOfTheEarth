#include "GameState.h"

void GameState::registerClickable(IClickable* element) {
	m_clickableElements.insert(element);
}

void GameState::registerHoverable(IHoverable* element) {
	m_hoverableElements.insert(element);
}

void GameState::registerKeyboardListener(IKeyboardListener* element) {
	m_keyboardListeners.insert(element);
}

std::set<IClickable*>* GameState::getClickableElements() {
	return &m_clickableElements;
}

std::set<IHoverable*>* GameState::getHoverableElements() {
	return &m_hoverableElements;
}

std::set<IKeyboardListener*>* GameState::getKeyboardListeners() {
	return &m_keyboardListeners;
}

std::set<IHoverable*>* GameState::getCurrentlyHoveredElements() {
	return &m_currentlyHoveredElements;
}
