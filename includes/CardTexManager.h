///\file
#ifndef CARDTEXMANAGER_H_
#define CARDTEXMANAGER_H_

#include "Game.h"

class CardTexManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName);
};

#endif /* CARDTEXMANAGER_H_ */
