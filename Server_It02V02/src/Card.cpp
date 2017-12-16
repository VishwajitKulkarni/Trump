///\file
/*
*  details   Implementation of Trump game
*  author    Shubham Yadav (s1911996) (s.yadav@student.utwente.nl)
*  version   1.2
*  date      Created on : 23 November 2017\n
			  Last Modified on : 12 December 2017
*/

#include <iostream>
#include "Card.h"
#include "TrumpMisc.h"

/**
* Constructor with no input arguments. Initializes all class fields to their default values.
*/
Card::Card()
{
	this->suit = SUITS::DEFAULT;
	this->cardNumber = 0;
	this->cardValid = false;
}

/**
* Setter function to set the suit of a card
* @param suit Suit of card
*/
void Card::setSuit(SUITS suit)
{
	this->suit = suit;
}

/**
* Getter function to get the suit of a card
* @return Suit of a card
*/
SUITS Card::getSuit(void)
{
	return this->suit;
}

/**
* Setter function to set the number of a card
* @param cardnumber Number of a card
*/
void Card::setCardNumber(int cardnumber)
{
	this->cardNumber = cardnumber;
}

/**
* Getter function to get the number of card
* @return Number of a card
*/
int Card::getCardNumber(void)
{
	return this->cardNumber;
}

/**
* Setter function for setting validity of card
* @param validity validity of card which is true when card is available in game, else false.
*/
void Card::setCardValidity(bool validity)
{
//	std::cout<<"Is this getting displyed:10:"<<std::endl;
	this->cardValid = validity;
//	std::cout<<"Is this getting displyed:11:"<<std::endl;
}

/**
* Getter function for getting validity of card
* @return validity of card
*/
bool Card::getCardValidity()
{
	return this->cardValid;
}

/**
* Function to print attributes of card
*/
void Card::toString(void)
{
	switch (this->suit)
	{
	case SUITS::HEARTS: std::cout << "H " << this->cardNumber << std::endl;
		break;
	case SUITS::CLUBS: std::cout << "C " << this->cardNumber << std::endl;
		break;
	case SUITS::DIAMONDS: std::cout << "D " << this->cardNumber << std::endl;
		break;
	default: std::cout << "S " << this->cardNumber << std::endl;
		break;
	}
}

/**
* Destructor for class Card
*/
Card::~Card()
{
	std::cout << "Destructor for class Card called" << std::endl;
}
