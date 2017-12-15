///\file

/**
 * Game.h
 *
 *  Created on: Dec 5, 2017
 *      Author: husain
 */

#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <string.h>
#include <vector>
#include "Cards.h"
#include <SDL2/SDL_ttf.h>

#define  SCREEN_WIDTH  1280
#define  SCREEN_HEIGHT  768

class Game {
public:
	Game();
	~Game();

	void init(int xpos, int ypos, int width, int height);

	bool handleEvent();
	void update();
	void Renderer();
	void loadAllCards();
	void playerMove();
	void RenderPL();
	void RenderPU();
	void RenderPR();
	void RenderTrumpSelect();
	void Load5Cards();
	void RenderIP();
	void clean();
	void load(std::string file, char s, int n);
	void button(int x, int y);
	void selectTrumpButton(int x, int y);
	void LoadPL(std::string fileName, char s, int n);
	void LoadPU(std::string fileName, char s, int n);
	void LoadPR(std::string fileName, char s, int n);
	void trumpTex(std::string file);
	void score(char a, char b);
	void playerIDTex();

	static SDL_Renderer *renderer;

	bool running() {
		return isRunning;
	}

	bool isMyTurn() const {
		return myTurn;
	}

	void setMyTurn(bool myTurn) {
		this->myTurn = myTurn;
	}

	int getPlayedCard() const {
		return playedCard;
	}

	char getPlayedSuit() const {
		return playedSuit;
	}

	char getTrump() const {
		return Trump;
	}

	void setIp(bool ip) {
		this->ip = ip;
	}

	void setTakebutton(bool takebutton) {
		Takebutton = takebutton;
	}

	void setTakeTrump(bool takeTrump) {
		TakeTrump = takeTrump;
	}

	void setShowTrump(bool showTrump) {
		this->showTrump = showTrump;
	}

	bool isTakeTrump() const {
		return TakeTrump;
	}

	const std::string& getIpString() const {
		return ip_string;
	}

	void setShowScore(bool showScore) {
		this->showScore = showScore;
	}

	void setIdDown(const std::string& idDown) {
		IDDown = idDown;
	}

	void setIdLeft(const std::string& idLeft) {
		IDLeft = idLeft;
	}

	void setIdRight(const std::string& idRight) {
		IDRight = idRight;
	}

	void setIdUp(const std::string& idUp) {
		IDUp = idUp;
	}

private:
	char playedSuit;
	int playedCard;
	bool myTurn;
	char Trump;
	bool isRunning;
	SDL_Window *window;
	TTF_Font* ip_font;
	SDL_Texture* ip_texture;
	SDL_Texture* TeamATex;
	SDL_Texture* TeamBTex;
	SDL_Rect ip_Rect;
	SDL_Color ip_color;
	SDL_Surface* surface;
	SDL_Texture* backgroundtex;
	SDL_Texture* suitSelectTex;
	SDL_Texture* TrumpTex;
	SDL_Texture* TrumpSuitTex;
	SDL_Texture* textTex;
	SDL_Rect TrumpText;
	SDL_Rect TrumpSuit;
	SDL_Rect suitsDisplay;
	SDL_Rect text;
	std::string ip_string;
	bool ip;
	bool Takebutton;
	bool TakeTrump;
	bool showTrump;
	bool PlayerLeft;
	bool PlayerUp;
	bool PlayerRight;
	char scoreTeamA;
	char scoreTeamB;
	std::string TeamA;
	std::string TeamB;
	SDL_Rect TeamARect;
	SDL_Rect TeamBRect;
	bool showScore;
	TTF_Font* playerIDFont;
	SDL_Texture* playerIDDown;
	SDL_Texture* playerIDLeft;
	SDL_Texture* playerIDUp;
	SDL_Texture* playerIDRight;
	SDL_Rect playerIDRect;
	SDL_Color playerIDColor;
	std::string IDDown;
	std::string IDLeft;
	std::string IDRight;
	std::string IDUp;
};

#endif /* GAME_H_ */
