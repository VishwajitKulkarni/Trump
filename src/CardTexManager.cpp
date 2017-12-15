///\file
#include "CardTexManager.h"

SDL_Texture* CardTexManager::LoadTexture(const char* fileName) {
	SDL_Surface* tempsurface = IMG_Load(fileName);
	SDL_Texture* cardTex = SDL_CreateTextureFromSurface(Game::renderer,
			tempsurface);
	SDL_FreeSurface(tempsurface);
	return cardTex;

}
