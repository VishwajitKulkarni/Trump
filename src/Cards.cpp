///\file
#include "Cards.h"
#include "CardTexManager.h"

Cards::Cards(const char* cardTex, int x, int y, char s, int n, bool ACTIVE) {
	tex = CardTexManager::LoadTexture(cardTex);
	xpos = x;
	ypos = y;
	suit = s;
	num = n;
	isActive = ACTIVE;
}

void Cards::update() {

	destR.x = xpos;
	destR.y = ypos;
	destR.h = 150;
	destR.w = 75;

}
void Cards::Render() {
	SDL_RenderCopy(Game::renderer, tex, NULL, &destR);
}

Cards::~Cards() {

}
