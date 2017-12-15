#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"
#include "GUI.h"
#include <SDL2/SDL_image.h>


int main(int argc, const char * argv[]) {



	std::string IP;
	char suit;
	int num = 0;
	char trump;
	char A='7';
	char B='0';
	GUI* gui = new GUI();
	gui->initialize();
	gui->DisplayWindowForIP();
	std::cout<<gui->getIP()<<std::endl;
	gui->loadPlayerID("Player 1","Player 2","Player 3","Player 4");
	for (int var = 0; var < 13; ++var) {
	gui->loadPlayerHand('H',14);
	}
	gui->Display5Cards();
	gui->AskTrump();
	gui->displayAllCards();
	gui->setTrump();
	gui->updateScore(A,B);

	SDL_Delay(9000);

	gui->close();
	return 0;
}

