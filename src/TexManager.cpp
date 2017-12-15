///\file
#include "TexManager.h"

SDL_Texture* TexManager::LoadTexture(const char* fileName) {
	SDL_Surface* tempsurface = IMG_Load(fileName);
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(Game::renderer,
			tempsurface);
	SDL_FreeSurface(tempsurface);
	return Tex;

}

SDL_Texture* TexManager::LoadTextureFromString(const char* fileName,TTF_Font* font,SDL_Color color){
	SDL_Surface* tempsurface = TTF_RenderText_Solid(font, fileName, color);
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(Game::renderer, tempsurface);
		SDL_FreeSurface(tempsurface);
		return Tex;
}
