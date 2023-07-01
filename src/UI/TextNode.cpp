#include "TextNode.h"

void TextNode::createTextTexture(SDL_Renderer* renderer) {
	// open font if it isn't open
	if (!m_font) {
		setFont(DEFAULT_FONT, DEFAULT_FONT_SIZE);
	}

	m_textTexture = SDLUtils::createTextTexture(
		renderer, m_font, m_nodeText.c_str(), m_fontColor, m_wrapped);

	SDL_SetTextureScaleMode(m_textTexture, SDL_ScaleModeBest); // for better text scaling
}

TextNode::~TextNode() {
	if (m_font) TTF_CloseFont(m_font);
	if (m_textTexture) SDL_DestroyTexture(m_textTexture);
}

TextNode::TextNode(const std::string& text, const std::string& fontFile, const int fontSize) : 
		m_nodeText{ text }, m_textTexture{ nullptr }, m_font{ nullptr },  m_fontSize{fontSize},
		m_fontColor{ DEFAULT_FONT_COLOR }, m_wrapped{ false } {
	// open font so text dimensions can be computed, only render texture when it needs to be drawn
	setFont(fontFile, fontSize);
	TTF_SizeText(m_font, m_nodeText.c_str(), &m_w, &m_h);
}

void TextNode::setFontColor(const SDL_Color& color) {
	m_fontColor = color;
}

void TextNode::setFontSize(const int size) {
	TTF_SetFontSize(m_font, size);
	TTF_SizeText(m_font, m_nodeText.c_str(), &m_w, &m_h); // recompute dimensions
}

void TextNode::setText(const std::string& text) {
	m_nodeText = text;
	TTF_SizeText(m_font, text.c_str(), &m_w, &m_h); // recompute dimensions

	// destroy old texture
	if (m_textTexture) {
		SDL_DestroyTexture(m_textTexture);
	}

	m_textTexture = nullptr;
}

void TextNode::setFont(const std::string& file, int fontSize) {
	if (m_font) {
		TTF_CloseFont(m_font);
	}

	m_font = TTF_OpenFont(file.c_str(), fontSize);
	TTF_SizeText(m_font, m_nodeText.c_str(), &m_w, &m_h); // recompute dimensions

	if (!m_font) {
		SDLUtils::error("TextNode::setFont OpenFont");
	}
}

void TextNode::setWrapped(const bool wrap) {
	m_wrapped = wrap;
}

void TextNode::draw(SDL_Renderer* renderer) {
	if (!m_shown) return;
	SDL_Rect textRect{ m_x, m_y, m_w, m_h };

	// draw texture if it isn't already drawn
	if (!m_textTexture) {
		createTextTexture(renderer);
	}

	SDL_RenderCopy(renderer, m_textTexture, NULL, &textRect);
}