#include "TextNode.h"

void TextNode::createTextTexture() {
	if (m_textTexture) SDL_DestroyTexture(m_textTexture); // destory old texture

	m_textTexture = SDLUtils::createTextTexture(
		m_renderer, m_font, m_nodeText.c_str(), m_fontColor, m_wrapped);

	// fill in class attributes
	SDL_QueryTexture(m_textTexture, NULL, NULL, &m_textBounds.w, &m_textBounds.h);

	// set container size to text size if no custom size specified
	if (!m_customBoundsSet) { 
		m_bounds.w = m_textBounds.w;
		m_bounds.h = m_textBounds.h;
	}

	SDL_SetTextureScaleMode(m_textTexture, SDL_ScaleModeBest); // for better text scaling
}

TextNode::~TextNode() {
	if (m_font) TTF_CloseFont(m_font);
	if (m_textTexture) SDL_DestroyTexture(m_textTexture);
}

TextNode::TextNode(SDL_Renderer* renderer, const std::string& text,
	const int fontSize, const bool wrapped, const std::string& fontFile)
	: Drawable(renderer),
	m_nodeText{ text },
	m_textTexture{ nullptr },
	m_font{ nullptr },
	m_textBounds{0,0,0,0},
	m_fontSize{fontSize}, 
	m_fontColor{ DEFAULT_FONT_COLOR },
	m_wrapped{ wrapped } {

	setFont(fontFile, fontSize); // open font
	TTF_SetFontWrappedAlign(m_font, DEFAULT_WRAP_ALIGN);
	createTextTexture(); // draw texture so attributes are filled
}

void TextNode::setFontColor(const SDL_Color& color) {
	m_fontColor = color;
	createTextTexture();
}

void TextNode::setFontSize(const int size) {
	TTF_SetFontSize(m_font, size);
	createTextTexture();
}

void TextNode::setText(const std::string& text) {
	m_nodeText = text;
	createTextTexture();
}

void TextNode::setFont(const std::string& file, int fontSize) {
	if (m_font) {
		TTF_CloseFont(m_font); // free memory
	}

	m_font = TTF_OpenFont(file.c_str(), fontSize);

	if (!m_font) {
		SDLUtils::error("TextNode::setFont OpenFont");
	}

	createTextTexture(); // recreate using new font
}

void TextNode::setWrapped(const bool wrap) {
	m_wrapped = wrap;
	createTextTexture();
}

SDL_Rect TextNode::getTextBounds() {
	return m_textBounds;
}

void TextNode::setSize(int w, int h) {
	Drawable::setSize(w, h); // default behavior

	m_customBoundsSet = true; // texture will be scaled to fit new bounds
}

void TextNode::draw() {
	if (!m_shown) return;
	SDL_Rect textRect{ m_bounds.x, m_bounds.y, m_bounds.w, m_bounds.h };

	SDL_RenderCopy(m_renderer, m_textTexture, NULL, &textRect);
}