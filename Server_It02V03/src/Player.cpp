///\file
/*
 *  details   Implementation of Trump game
 *  author    Shubham Yadav (s1911996) (s.yadav@student.utwente.nl)
 *  version   1.2
 *  date      Created on : 23 November 2017\n
 Last Modified on : 12 December 2017
 */

#include "Player.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Constructor with 1 input parameter which sets the state of player on network. It also
 * initializes all class fields to their default value.
 * @param state boolean variable representing whether player is active on network or not
 */
Player::Player(bool state) {
	this->isActive = state;
	this->isPlaying = false;
	this->team = TEAM::DEFAULT;
	this->playerID = ENTITY::DEFAULT;
	this->playerName = "NOT DEFINED";
	for (size_t i = 0; i < 13; i++) {
		currentCards[i] = NULL;
	}
}

/**
 * Getter function to get the player ID
 * @return player ID
 */
ENTITY Player::getPlayerID(void) {
	return this->playerID;
}

/**
 * Setter function to set the player ID
 * @param id player ID
 */
void Player::setPlayerID(ENTITY id) {
	this->playerID = id;
}

/**
 * Getter function to get the player name
 * @return player name
 */
std::string Player::getPlayername(void) {
	return this->playerName;
}

/**
 * Setter function to set the name of player
 * @param name player name
 */
void Player::setPlayername(std::string name) {
	this->playerName = name;
}

/**
 * Setter function to set the team of a player
 * @param team team to which a player belongs
 */
void Player::setTeam(TEAM team) {
	this->team = team;
}

/**
 * Getter function to get the team of a player
 * @return team to which a player belongs
 */
TEAM Player::getTeam(void) {
	return this->team;
}

/**
 * Function to assign 13 random cards to a player
 * @param card pointer to the array of pointers of object card
 */
void Player::set5Cards(Card** card) {
	for (int i = 0; i < 13; i++) {
//		std::cout << "Is this getting displyed:4:" << std::endl;
		int player= static_cast<int>(this->playerID);
		player--;
//		std::cout<<"Player "<<player<<std::endl;
		this->currentCards[i] = card[(player * 13) + i];
//		std::cout << "Is this getting displyed:5:" << std::endl;
		if (i > 4) {
//			std::cout << "Is this getting displyed:6:" << std::endl;
			if (this->currentCards[i] == NULL) {
//				std::cout << "NULL card exception" << std::endl;
			}
//			this->currentCards[i]->setCardValidity(false);
			this->currentCards[i]->toString();
		}
//		std::cout << "Is this getting displyed:7:" << std::endl;
	}
//	std::cout << "Is this getting displyed:8:" << std::endl;
}

void Player::setRestCards(void) {
	for (int i = 0; i < 13; i++) {
		this->currentCards[i]->setCardValidity(true);
	}
}

/**
 * Getter function to get the cards of a player
 * @return pointer to the array of pointers of card objects given to a player
 */
Card** Player::getCards(void) {
	return this->currentCards;
}

/**
 * Function to change the validity of card when it is played
 * @param playedcard pointer to the object card played by the player
 */
void Player::movePlayed(Card* playedcard) {
	for (size_t i = 0; i < 13; i++) {
		if ((currentCards[i]->getSuit() == playedcard->getSuit())
				&& (currentCards[i]->getCardNumber()
						== playedcard->getCardNumber())) {
			currentCards[i]->setCardValidity(false);
		}
	}
}

/**
 * Getter function to get the status of player playing or not
 * @return boolean which represents whether player is playing or not
 */
bool Player::getIsPlaying(void) {
	return this->isPlaying;
}

/**
 * Setter function to set the status of player whether playing or not
 * @param temp boolean value which is true when player is playing else false
 */
void Player::setIsPlaying(bool temp) {
	this->isPlaying = temp;
}

/**
 * Setter function to set the status of player whether active on network or not
 * @param temp boolean value which is true when player is active on network else false
 */
void Player::setIsActive(bool temp) {
	this->isActive = temp;
}

/**
 * Getter function to get the status of player whether active on network or not
 * @return boolean value representing whether player is active on network or not
 */
bool Player::getIsActive(void) {
	return this->isActive;
}

/**
 * Function to print player ID, player name and cards currently in hand of a playerr
 */
void Player::toString(void) {
	std::cout << "Player " << static_cast<int>(playerID) + 1 << " "
			<< this->playerName << " has following cards :" << std::endl;
	for (size_t i = 0; i < 13; i++) {
		if (currentCards[i]->getCardValidity() == true) {
			std::cout
					<< (currentCards[i]->getSuit() == SUITS::HEARTS ? 'H' :
						currentCards[i]->getSuit() == SUITS::DIAMONDS ? 'D' :
						currentCards[i]->getSuit() == SUITS::CLUBS ? 'C' : 'S')
					<< " " << currentCards[i]->getCardNumber() << ", ";
		}
	}
	std::cout << std::endl;
}

/**
 * Destructor for class Player
 */
Player::~Player() {
	std::cout << "Destructor for Player class called" << std::endl;
}
