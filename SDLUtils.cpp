#include "SDLUtils.h"

void SDLUtils::error(const std::string& msg) {
	LOGGER << msg << " Error: " << SDL_GetError() << std::endl;
}

std::string SDLUtils::getResourceDirPath(const std::string& subDir) {
	// set path seperator by platform
#ifdef _WIN32 
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif

	static std::string baseResPath;

	if (baseResPath.empty()) {
		char* newPath = SDL_GetBasePath();

		if (newPath) {
			baseResPath = newPath;
			SDL_free(newPath);
		}
		else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
		}

		// find last PATH_SEP, excluding trailing one
		size_t appDirectoryIndex = baseResPath.rfind(PATH_SEP, baseResPath.length() - 2);

		// move into parent directory, add back training path PATH_SEP
		baseResPath = baseResPath.substr(0, appDirectoryIndex + 1);

		baseResPath = baseResPath + RESOURCE_DIR_NAME + PATH_SEP;
	}

	return subDir.empty() ? baseResPath : baseResPath + subDir + PATH_SEP;
}

SDL_Texture* SDLUtils::loadTexture(SDL_Renderer* renderer, const std::string& file) {
	SDL_Texture* newTex = nullptr;

	newTex = IMG_LoadTexture(renderer, file.c_str());

	if (newTex == nullptr) {
		error("CreateTextureFromSurface");
	}

	return newTex;
}

void SDLUtils::renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y) {
	SDL_Rect newRect = { x, y };

	SDL_QueryTexture(texture, NULL, NULL, &newRect.w, &newRect.h); // default to texture width & height
	SDL_RenderCopy(renderer, texture, NULL, &newRect);
}

void SDLUtils::renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h) {
	SDL_Rect newRect = { x, y, w, h };

	SDL_RenderCopy(renderer, texture, NULL, &newRect);
}