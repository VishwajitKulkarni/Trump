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

#include "GameManager.h"

int main(int argc, char **argv) {
	Message txFrame, rxFrame;
//	Server server(&txFrame, &rxFrame);
	GameManager gameManager(&txFrame, &rxFrame);
	gameManager.handleNetworkThreadCallback();
//	server.createNetworkThread();
//	gameManager.createNetworkThread();
//	while(1);
}
