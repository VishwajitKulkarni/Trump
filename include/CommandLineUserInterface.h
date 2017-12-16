///\file
/*!
*  \details     Implementation of Trump game
*  \author    Shubham Yadav (s.yadav@student.utwente.nl)
*  \version   1.0
*  \date      23 November 2017
*/

#ifndef COMMAND_LINE_USER_INTERFACE_H
#define COMMAND_LINE_USER_INTERFACE_H

#include <iostream>
#include "Card.h"
#include "TrumpMisc.h"
#include "Player.h"

class CommandLineUserInterface
{
private:
	std::string print_str;/*!< temporary string used for printing*/
public:
	CommandLineUserInterface();
	void displayPlayerMoves(Player*,Card*);
	void playerJoinWith5Cards(Player*);
	void playerWithAllCards(Player*);
	void printString(std::string);
	~CommandLineUserInterface();
};

#endif