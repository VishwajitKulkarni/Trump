///\file
/*
*  Author    Shubham Yadav (s.yadav@student.utwente.nl)
*  Version   1.0
*  Date      23 November 2017
*  Brief     Implementation of Trump game
*/

#include "CommandLineUserInterface.h"
#include <string>


/**
* Blank constructor with no input arguments
*/
CommandLineUserInterface::CommandLineUserInterface()
{
	//empty constructor
}

/**
* Function to display moves of a player on the command line interface
* @param player pointer to the object of type player
* @param card pointer to the object of type card
*/
void CommandLineUserInterface::displayPlayerMoves(Player* player, Card* card)
{
	//display recent moves and card left of player
	//displaying current move
	std::cout << "\nPlayer " << (static_cast<int>(player->getPlayerID())) << " " << player->getPlayername() << " played ";
	switch (card->getCardNumber())
	{
	case 14: std::cout << "ACE ";
		break;
	case 13: std::cout << "KING ";
		break;
	case 12: std::cout << "QUEEN ";
		break;
	case 11: std::cout << "JACK ";
		break;
	default: std::cout << card->getCardNumber() << " ";
		break;
	}
	std::cout << "of ";
	switch (card->getSuit())
	{
	case SUITS::HEARTS: std::cout << "HEARTS";
		break;
	case SUITS::CLUBS: std::cout << "CLUBS";
		break;
	case SUITS::DIAMONDS: std::cout << "DIAMONDS";
		break;
	case SUITS::SPADES: std::cout << "SPADES";
		break; 
	default: std::cout << "UNKNOWN";
		break;
	}
	std::cout << std::endl;

	//display remaining cards of same player
	std::cout << "Player " << (static_cast<int>(player->getPlayerID())) << " " << player->getPlayername() << " has card left: ";

	for (size_t i = 0; i < 13; i++)
	{
		if(player->getCards()[i]->getCardValidity() == true)
		{
			switch (player->getCards()[i]->getSuit())
			{
			case SUITS::CLUBS: std::cout << "C ";
				break;
			case SUITS::DIAMONDS: std::cout << "D ";
				break;
			case SUITS::HEARTS: std::cout << "H ";
				break;
			case SUITS::SPADES: std::cout << "S ";
				break;
			default: std::cout << "UNKNOWN ";
				break;
			}

			std::cout << player->getCards()[i]->getCardNumber() << ", ";
		}
	}
	std::cout << std::endl;
}

/**
* Function to display the joining of player and the cards alloted to him at start on the command line
* @param player pointer to the object of type player
*/
void CommandLineUserInterface::playerJoinWith5Cards(Player* player)
{
	//display which player joined
	std::cout << "\nPlayer " << (static_cast<int>(player->getPlayerID())) << " " << player->getPlayername() <<
		" joined the game. Player is in Team " << ((player->getTeam() == TEAM::TEAMA) ? "A" : "B" )<< std::endl;
		
	std::cout << player->getPlayername() << " has :";

	for (size_t i = 0; i < 13; i++)
	{
		if (player->getCards()[i]->getCardValidity() == true)
		{
			switch (player->getCards()[i]->getSuit())
			{
			case SUITS::CLUBS: std::cout << "C ";
				break;
			case SUITS::DIAMONDS: std::cout << "D ";
				break;
			case SUITS::HEARTS: std::cout << "H ";
				break;
			case SUITS::SPADES: std::cout << "S ";
				break;
			default: std::cout << "UNKNOWN ";
				break;
			}

			std::cout << player->getCards()[i]->getCardNumber() << ", ";
		}
	}
	std::cout << std::endl;
}

/**
* Function to display the remaining cards of player
* @param player pointer to the object of type player
*/
void CommandLineUserInterface::playerWithAllCards(Player* player)
{
	//display which player joined
	std::cout << "\nPlayer " << (static_cast<int>(player->getPlayerID())) << " " << player->getPlayername() <<
		" now has :";

	for (size_t i = 0; i < 13; i++)
	{
		if (player->getCards()[i]->getCardValidity() == true)
		{
			switch (player->getCards()[i]->getSuit())
			{
			case SUITS::CLUBS: std::cout << "C ";
				break;
			case SUITS::DIAMONDS: std::cout << "D ";
				break;
			case SUITS::HEARTS: std::cout << "H ";
				break;
			case SUITS::SPADES: std::cout << "S ";
				break;
			default: std::cout << "UNKNOWN ";
				break;
			}

			std::cout << player->getCards()[i]->getCardNumber() << ", ";
		}
	}
	std::cout << std::endl;
}

/**
* Function to print a string
* @param str string given by caller
*/
void CommandLineUserInterface::printString(std::string str)
{
	//print normal string
	std::cout << str ;
}

/**
* Destructor for class Command line user Interface
*/
CommandLineUserInterface::~CommandLineUserInterface()
{
	std::cout << "Destructor of Command line user interface called." << std::endl;
}
