#pragma once

#include <SDL2/SDL.h>
#include <iostream>

namespace SDLUtils {
	// constants
	inline const char* const RESOURCE_DIR_NAME = "res";
	inline std::ostream& LOGGER = std::cout; // direct error messages here

	// push an error message of format [msg] Error: [SDL_GetLastError()] into LOGGER
	void error(const std::string& msg = "");

	// get the path to the resource directory + optional subdirectory
	std::string getResourceDirPath(const std::string& subDir = "");

	// load texture from bmp file
	SDL_Texture* loadBMPTexture(SDL_Renderer* renderer, const std::string& file);
}
