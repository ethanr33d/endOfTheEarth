#include "GameState.h"

void GameState::registerClickable(IClickable* element) {
	clickableElements.insert(element);
}

void GameState::registerHoverable(IHoverable* element) {
	hoverableElements.insert(element);
}

std::set<IClickable*>* GameState::getClickableElements() {
	return &clickableElements;
}

std::set<IHoverable*>* GameState::getHoverableElements() {
	return &hoverableElements;
}