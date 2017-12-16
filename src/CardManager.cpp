///\file
/*
*  details   Implementation of Trump game
*  author    Shubham Yadav (s1911996) (s.yadav@student.utwente.nl)
*  version   1.2
*  date      Created on : 23 November 2017\n
     		  Last Modified on : 12 December 2017
*/

#include "CardManager.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>    
#include <ctime>

/**
* function that generates random number
* used as a supplementary function for standard library function
* @param num input parameter of type integer
* @return randomly generated number
*/
int myrandom(int num)
{ 
	return std::rand() % num; 
}


/**
* Constructor with no input arguments.\n
* Instantiates array of pointers of 52 cards.\n
* Shuffles the array of pointers which inturn shuffles the deck of cards.
*/
CardManager::CardManager()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			allCards[(i * 13) + j] = new Card(); // object created

			// spades (3) , clubs (2) , diamonds (1) , hearts (0)
			allCards[(i * 13) + j]->setSuit(static_cast<SUITS>(i));
			// Ace -> 14, King -> 13, Queen -> 12 .....
			allCards[(i * 13) + j]->setCardNumber(j+2);
			allCards[(i * 13) + j]->setCardValidity(true);
		}
	}
	// after creation of all cards, shuffle them
	shuffleCards();
}

/**
* Function to shuffle cards using standard library functions
*/
void CardManager::shuffleCards()
{
	//shuffled in a group of 13 and at last shuffled in a group of 52
	std::srand(unsigned(std::time(0)));
	std::random_shuffle(&allCards[0], &allCards[12], myrandom); // shuffle 1-13 cards
	std::random_shuffle(&allCards[13], &allCards[25], myrandom); // shuffle 14-26 cards
	std::random_shuffle(&allCards[26], &allCards[38], myrandom); // shuffle 27-39 cards
	std::random_shuffle(&allCards[39], &allCards[51], myrandom); // shuffle 40-52 cards
	std::random_shuffle(std::begin(allCards), std::end(allCards), myrandom); // shuffle 1-52 cards
}

/**
* Getter function to get shuffled cards
* @return pointer to the array of pointers of objects of class card
*/
Card** CardManager::getshuffledCards(void)
{
	return this->allCards;
}

/**
* Function to print all cards
* Cards will appear in a shuffled manner
*/
void CardManager::toString()
{
	for (size_t i = 0; i < 52; i++)
	{
		switch (allCards[i]->getSuit())
		{
		case SUITS::HEARTS: std::cout << "H " << allCards[i]->getCardNumber() << std::endl;
			break;
		case SUITS::CLUBS: std::cout << "C " << allCards[i]->getCardNumber() << std::endl;
			break;
		case SUITS::DIAMONDS: std::cout << "D " << allCards[i]->getCardNumber() << std::endl;
			break;
		case SUITS::SPADES: std::cout << "S " << allCards[i]->getCardNumber() << std::endl;
			break;
		default : std::cout << "UNKNOWN CARDS" << std::endl;
		}
	}
}

/**
* Destructor for class Card manager
*/
CardManager::~CardManager()
{
	std::cout << "Destructor for Card Manager class called" << std::endl;
}
