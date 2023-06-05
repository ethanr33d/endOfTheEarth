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

SDL_Texture* SDLUtils::loadBMPTexture(SDL_Renderer* renderer, const std::string& file) {
	SDL_Texture* newTex = nullptr;
	SDL_Surface* newSurface = nullptr;

	newSurface = SDL_LoadBMP(file.c_str());

	if (newSurface != nullptr) {
		newTex = SDL_CreateTextureFromSurface(renderer, newSurface);
		SDL_FreeSurface(newSurface);

		if (newTex == nullptr) {
			error("CreateTextureFromSurface");
		}
	}
	else {
		error("LoadBMP");
	}


	return newTex;
}