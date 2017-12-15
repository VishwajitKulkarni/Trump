///\file
/**
 * Cards.h
 *
 *  Created on: Dec 6, 2017
 *      Author: husain
 */

#ifndef SRC_CARDS_H_
#define SRC_CARDS_H_
#include "Game.h"

class Cards {
public:
	Cards(const char* cardTex, int x, int y, char s, int n, bool ACTIVE);
	~Cards();

	void update();
	void Render();

	int getNum() const {
		return num;
	}

	int getXpos() const {
		return xpos;
	}

	int getYpos() const {
		return ypos;
	}

	void setXpos(int xpos) {
		this->xpos = xpos;
	}

	void setYpos(int ypos) {
		this->ypos = ypos;
	}

	int getDestRh() const {
		return destR.h;
	}
	int getDestRw() const {
		return destR.w;
	}

	bool isIsActive() const {
		return isActive;
	}

	void setIsActive(bool isActive) {
		this->isActive = isActive;
	}

	char getSuit() const {
		return suit;
	}
	char suit;
	int num;
	bool isActive;

private:

	int xpos;
	int ypos;



	SDL_Texture* tex;
	SDL_Rect destR;
};

#endif /* SRC_CARDS_H_ */
