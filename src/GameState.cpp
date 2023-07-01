#include "GameState.h"

void GameState::registerClickable(IClickable* element) {
	m_clickableElements.insert(element);
}

void GameState::registerHoverable(IHoverable* element) {
	m_hoverableElements.insert(element);
}

std::set<IClickable*>* GameState::getClickableElements() {
	return &m_clickableElements;
}

std::set<IHoverable*>* GameState::getHoverableElements() {
	return &m_hoverableElements;
}