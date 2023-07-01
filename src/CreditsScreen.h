//Credits screen state from the main menu
// inherits from HelpScreen class since they are so smiliar
#pragma once

#include "HelpScreen.h"

class CreditsScreen : public HelpScreen {
private:
	inline static const std::string CREDIT_TEXT = "Lovely Credits \n"
		"blah blah placeholder \n"
		"go test something else now \n";
public:
	CreditsScreen(Engine& engine);
	virtual void drawFrame();
};