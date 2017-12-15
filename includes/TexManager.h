///\file
#ifndef TEXMANAGER_H_
#define TEXMANAGER_H_

#include "Game.h"

class TexManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static SDL_Texture* LoadTextureFromString(const char* str,TTF_Font* font,SDL_Color color);
};

#endif /* CARDTEXMANAGER_H_ */
