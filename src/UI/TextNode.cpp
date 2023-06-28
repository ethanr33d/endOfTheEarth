#include "TextNode.h"

void TextNode::createTextTexture(SDL_Renderer* renderer) {
	// open font if it isn't open
	if (!font) {
		setFont(DEFAULT_FONT, DEFAULT_FONT_SIZE);
	}

	textTexture = SDLUtils::createTextTexture(renderer, font, nodeText.c_str(), fontColor, wrapped);

	SDL_SetTextureScaleMode(textTexture, SDL_ScaleModeBest); // for better text scaling
}

TextNode::~TextNode() {
	if (font) TTF_CloseFont(font);
	if (textTexture) SDL_DestroyTexture(textTexture);
}

TextNode::TextNode(const std::string& text, const std::string& fontFile, const int fontSize) : 
		nodeText{ text }, textTexture{ nullptr }, font{ nullptr },  fontSize{fontSize},
		fontColor{ DEFAULT_FONT_COLOR }, wrapped{ false } {
	// open font so text dimensions can be computed, only render texture when it needs to be drawn
	setFont(fontFile, fontSize);
	TTF_SizeText(font, nodeText.c_str(), &w, &h);
}

void TextNode::setFontColor(const SDL_Color& color) {
	fontColor = color;
}

void TextNode::setFontSize(const int size) {
	TTF_SetFontSize(font, size);
	TTF_SizeText(font, nodeText.c_str(), &w, &h); // recompute dimensions
}

void TextNode::setText(const std::string& text) {
	nodeText = text;
	TTF_SizeText(font, text.c_str(), &w, &h); // recompute dimensions

	// destroy old texture
	if (textTexture) {
		SDL_DestroyTexture(textTexture);
	}

	textTexture = nullptr;
}

void TextNode::setFont(const std::string& file, int fontSize) {
	if (font) {
		TTF_CloseFont(font);
	}

	font = TTF_OpenFont(file.c_str(), fontSize);
	TTF_SizeText(font, nodeText.c_str(), &w, &h); // recompute dimensions

	if (!font) {
		SDLUtils::error("TextNode::setFont OpenFont");
	}
}

void TextNode::setWrapped(const bool wrap) {
	wrapped = wrap;
}

void TextNode::draw(SDL_Renderer* renderer) {
	if (!shown) return;
	SDL_Rect textRect{ x, y, w, h };

	// draw texture if it isn't already drawn
	if (!textTexture) {
		createTextTexture(renderer);
	}

	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}