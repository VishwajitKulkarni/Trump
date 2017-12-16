/*
 * main.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: vishwajit
 */

#include <iostream>

#define cout std::cout
#define cin std::cin
#define endl std::endl
#include "Server.h"

int main(int argc, char **argv) {
//	SDL_mutex txMutex,rxMutex;
//	SDL_cond *cond;
	Message txFrame, rxFrame;
	Server server(&txFrame, &rxFrame);
	GameManager gameManager(&txFrame, &rxFrame);
	server.createNetworkThread();
	gameManager.createNetworkThread();
	while(1);
}
