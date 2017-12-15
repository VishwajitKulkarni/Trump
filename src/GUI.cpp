/*
 * GUI.cpp
 *
 *  Created on: Dec 7, 2017
 *      Author: husain
 */
#include"GUI.h"
#include <iostream>
#include <string>

GUI::GUI() {
	game = NULL;
	TrumpSuit = '0';
	flag = true;
	Quit = false;
	playedNum = 0;
	playedSuit = '0';
}

void GUI::initialize() {
	game = new Game;

	game->init(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
	SCREEN_HEIGHT);
	game->Renderer();

}

void GUI::DisplayWindowForIP() {
	IP = "";
	game->setIp(true);
	flag = true;
	while (flag && isRunning()) {

		flag = game->handleEvent();
		game->RenderIP();
		IP = game->getIpString();
	}
	if (IP.length() > 18) {
			IP = IP.substr(19, (IP.length() - 19));
		}

}

bool GUI::isRunning() {
	return game->running();
}

void GUI::loadPlayerHand(char suit, int num) {

	std::string fileName = "assets/xxx.png";
	fileName[9] = suit;
	std::string str = std::to_string(num);
	fileName.replace(7, 2, str);
	game->load(fileName, suit, num);
	std::cout<<fileName<<std::endl;

}

void GUI::Display5Cards() {

	game->Load5Cards();
	game->update();
	game->Renderer();

}

void GUI::AskTrump() {
	flag = true;
	game->setTakeTrump(true);

	game->Renderer();
	TrumpSuit = '0';
	while ((TrumpSuit != 'S' && TrumpSuit != 'C' && TrumpSuit != 'H'
			&& TrumpSuit != 'D') && isRunning() && game->isTakeTrump()) {
		game->handleEvent();
		TrumpSuit = game->getTrump();
		game->Renderer();
	}

}

void GUI::setTrump() {
	std::string fileName = "assets/x.png";
	fileName[7] = TrumpSuit;
	game->trumpTex(fileName);
	game->setShowTrump(true);
	game->Renderer();
}

void GUI::displayAllCards() {
	game->loadAllCards();
	game->Renderer();
}
void GUI::player(){
	game->setTakebutton(true);
		game->setMyTurn(true);
		while (game->isMyTurn() && isRunning()) {
			game->handleEvent();
			game->update();
			game->Renderer();
		}
		playedSuit = game->getPlayedSuit();
		playedNum = game->getPlayedCard();

}
void GUI::playerMove() {
	game->playerMove();
	game->update();
	game->Renderer();

}
void GUI::otherPlayers(char suit, int num, int whichPlayer) {
	game->handleEvent();
	switch (whichPlayer) {
	case 1:
		PL(suit, num);
		break;
	case 2:
		PU(suit, num);
		break;
	case 3:
		PR(suit, num);
		break;
	default:
		break;
	}
}

void GUI::updateScore() {
	game->setShowScore(true);
	game->score('1','1');
	game->Renderer();

}

void GUI::PL(char suit, int num) {
	std::string fileName = "assets/xx.png";
	fileName[8] = suit;
	std::string str = std::to_string(num);
	fileName.replace(7, 1, str);
	game->LoadPL(fileName, suit, num);
}

void GUI::PU(char suit, int num) {
	std::string fileName = "assets/xx.png";
	fileName[8] = suit;
	std::string str = std::to_string(num);
	fileName.replace(7, 1, str);
	game->LoadPU(fileName, suit, num);
}
void GUI::PR(char suit, int num) {
	std::string fileName = "assets/xx.png";
	fileName[8] = suit;
	std::string str = std::to_string(num);
	fileName.replace(7, 1, str);
	game->LoadPR(fileName, suit, num);
}

void GUI::close() {
	game->clean();
}

