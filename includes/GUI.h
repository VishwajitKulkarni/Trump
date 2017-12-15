/*
 * GUI.h
 *
 *  Created on: Dec 7, 2017
 *      Author: husain
 */

#ifndef SRC_GUI_H_
#define SRC_GUI_H_

#include"Game.h"
#include"Cards.h"
#include<string>

#define  SCREEN_WIDTH  1280
#define  SCREEN_HEIGHT  768

class GUI{

public:
	 GUI();
	 ~GUI();
	void initialize();
	void DisplayWindowForIP();
	void Display5Cards();
	void AskTrump();
	char getTrump() const {
			return TrumpSuit;
		}
	void setTrump();
	void displayAllCards();
	bool isRunning();
	void loadPlayerHand(char suit,int num);
	void player();
	void playerMove();
	void otherPlayers(char suit,int num,int whichPlayer);
	void PL(char suit,int num);
	void PR(char suit,int num);
	void PU(char suit,int num);
	void updateScore();

	void close();
	std::string getIP() {

		return IP;

	}

	int getPlayedNum() const {
		return playedNum;
	}

	char getPlayedSuit() const {
		return playedSuit;
	}

private:
	Game* game;
	char TrumpSuit;
	std::string IP;
	bool flag;
	bool Quit;
	char playedSuit;
	int playedNum;
};



#endif /* SRC_GUI_H_ */
