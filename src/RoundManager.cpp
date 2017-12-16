///\file
/*
*  Author    Shubham Yadav (s.yadav@student.utwente.nl)
*  Version   1.0
*  Date      23 November 2017
*  Brief     Implementation of Trump game
*/

#include <iostream>
#include "RoundManager.h"


/**
* Constructor with 3 input parameters
* @param suit trump suit
*/
RoundManager::RoundManager(SUITS suit)
{
	this->trump = suit;
	this->roundCount = 1;
	this->scoreTeamA = 0;
	this->scoreTeamB = 0;
	this->player1Score = 0;
	this->player2Score = 0;
	this->player3Score = 0;
	this->player4Score = 0;
	this->lastPlayerWon = ENTITY::DEFAULT;
}

/**
* Function to increase the count of rounds after every round
*/
void RoundManager::increaseRoundCount(void)
{
	this->roundCount++;
}

/**
* Getter function to get the suit of trump
* @return suit of trump
*/
SUITS RoundManager::getTrump(void)
{
	return this->trump;
}

/**
* Setter function to set the suit of trump
* @param suit suit of trump
*/
void RoundManager::setTrump(SUITS suit)
{
	this->trump = suit;
}

/**
* Getter function to get the no of rounds played till current time
* @return count of rounds
*/
int RoundManager::getRoundCount(void)
{
	return this->roundCount;
}

/**
* Getter function to get the score of team A
* @return score of team A
*/
int RoundManager::getScoreTeamA(void)
{
	this->scoreTeamA = this->player1Score + this->player3Score;
	return this->scoreTeamA;
}

/**
* Getter function to get the score of team B
* @return score of team B
*/
int RoundManager::getScoreTeamB(void)
{
	this->scoreTeamB = this->player2Score + this->player4Score;
	return this->scoreTeamB;
}

/**
* Getter function to get the id of player who won the last round
* @return player ID of player who won the last round
*/
ENTITY RoundManager::getLastPlayerWon(void)
{
	return this->lastPlayerWon;
}

/**
* Function which determines the result of round based on the cards played by the players
* @param player1card pointer to the object card played by player 1
* @param player2card pointer to the object card played by player 2
* @param player3card pointer to the object card played by player 3
* @param player4card pointer to the object card played by player 4
* @param currentsuit base suit of current round
*/
void RoundManager::checkRound(Card** cardPlayed, SUITS currentsuit)
{
	// make copies of players suit and card numbers
	// writing if statements will be easy
	// sx : s-> suit , x-> player no
	// cx : c-> card number , x-> playerno
	SUITS s1 = cardPlayed[0]->getSuit();
	SUITS s2 = cardPlayed[1]->getSuit();
	SUITS s3 = cardPlayed[2]->getSuit();
	SUITS s4 = cardPlayed[3]->getSuit();

	int c1 = cardPlayed[0]->getCardNumber();
	int c2 = cardPlayed[1]->getCardNumber();
	int c3 = cardPlayed[2]->getCardNumber();
	int c4 = cardPlayed[3]->getCardNumber();

	// now check who won the round
	if(s1 == s2 && s2 == s3 && s3 == s4)
	{
		// all cards are of same suit
		if (c1 > c2 && c1 > c3	&& c1 > c4)
		{
			// all cards are of same suit
			// player1 has highest card
			player1Score++;
			this->lastPlayerWon = ENTITY::PLAYER1;
		}
		else if (c2 > c1 && c2 > c3 && c2 > c4)
		{
			// all cards are of same suit
			// player2 has highest card
			player2Score++;
			this->lastPlayerWon = ENTITY::PLAYER2;
		}
		else if (c3 > c1 && c3 > c2 && c3 > c4)
		{
			// all cards are of same suit
			// player3 has highest card
			player3Score++;
			this->lastPlayerWon = ENTITY::PLAYER3;
		}
		else
		{
			// all cards are of same suit
			// player4 has highest card
			player4Score++;
			this->lastPlayerWon = ENTITY::PLAYER4;
		}
	}
	else
	{
		// some cards are of different suits
		// first check if there is any trump
		if (s1 == this->trump || s2 == this->trump || s3 == this->trump || s4 == this->trump)
		{
			// some cards are of different suit
			//someone played trump
			if (s1 == this->trump && s2 != this->trump && s3 != this->trump && s4 != this->trump)
			{
				// some cards are of different suits
				// player1 played trump
				player1Score++;
				this->lastPlayerWon = ENTITY::PLAYER1;
			}
			else if (s1 != this->trump && s2 == this->trump && s3 != this->trump && s4 != this->trump)
			{
				// some cards are of different suits
				// player2 played trump
				player2Score++;
				this->lastPlayerWon = ENTITY::PLAYER2;
			}
			else if (s1 != this->trump && s2 != this->trump && s3 == this->trump && s4 != this->trump)
			{
				// some cards are of different suits
				// player3 played trump
				player3Score++;
				this->lastPlayerWon = ENTITY::PLAYER3;
			}
			else if (s1 != this->trump && s2 != this->trump && s3 != this->trump && s4 == this->trump)
			{
				// some cards are of different suits
				// player 4 played trump
				player4Score++;
				this->lastPlayerWon = ENTITY::PLAYER4;
			}
			else if (s1 == this->trump && s2 == this->trump && s3 != this->trump && s4 != this->trump)
			{
				// some cards are of different suits
				// player 1 and player 2 played trump
				if (c1 > c2) { player1Score++; this->lastPlayerWon = ENTITY::PLAYER1; }
				else { player2Score++; this->lastPlayerWon = ENTITY::PLAYER2; }
			}
			else if (s1 == this->trump && s2 != this->trump && s3 == this->trump && s4 != this->trump)
			{
				// some cards are of different suits
				// player 1 and player 3 played trump
				if (c1 > c3) { player1Score++; this->lastPlayerWon = ENTITY::PLAYER1; }
				else { player3Score++; this->lastPlayerWon = ENTITY::PLAYER3; }
			}
			else if (s1 == this->trump && s2 != this->trump && s3 != this->trump && s4 == this->trump)
			{
				// some cards are of different suits
				// player 1 and player 4 played trump
				if (c1 > c4) { player1Score++; this->lastPlayerWon = ENTITY::PLAYER1; }
				else { player4Score++; this->lastPlayerWon = ENTITY::PLAYER4; }
			}
			else if (s1 != this->trump && s2 == this->trump && s3 == this->trump && s4 != this->trump)
			{
				// some cards are of different suits
				// player 2 and player 3 played trump
				if (c2 > c3) { player2Score++; this->lastPlayerWon = ENTITY::PLAYER2; }
				else { player3Score++; this->lastPlayerWon = ENTITY::PLAYER3; }
			}
			else if (s1 != this->trump && s2 == this->trump && s3 != this->trump && s4 == this->trump)
			{
				// some cards are of different suits
				// player 2 and player 4 played trump
				if (c2 > c4) { player2Score++; this->lastPlayerWon = ENTITY::PLAYER2; }
				else { player4Score++; this->lastPlayerWon = ENTITY::PLAYER4; }
			}
			else if (s1 != this->trump && s2 != this->trump && s3 == this->trump && s4 == this->trump)
			{
				// some cards are of different suits
				// player 3 and player 4 played trump
				if (c3 > c4) { player3Score++; this->lastPlayerWon = ENTITY::PLAYER3; }
				else { player4Score++; this->lastPlayerWon = ENTITY::PLAYER4; }
			}
			else if (s1 == this->trump && s2 == this->trump && s3 == this->trump && s4 != this->trump)
			{
				// some cards are of different suits
				// player 1 and player 2 and player 3 played trump
				if (c1 > c2 && c1 > c3) { player1Score++; this->lastPlayerWon = ENTITY::PLAYER1; }
				else if (c2 > c1 && c2 > c3) { player2Score++; this->lastPlayerWon = ENTITY::PLAYER2; }
				else { player3Score++; this->lastPlayerWon = ENTITY::PLAYER3; }
			}
			else if (s1 == this->trump && s2 == this->trump && s3 != this->trump && s4 == this->trump)
			{
				// some cards are of different suits
				// player 1 and player 2 and player 4 played trump
				if (c1 > c2 && c1 > c4) { player1Score++; this->lastPlayerWon = ENTITY::PLAYER1; }
				else if (c2 > c1 && c2 > c4) { player2Score++; this->lastPlayerWon = ENTITY::PLAYER2; }
				else { player4Score++; this->lastPlayerWon = ENTITY::PLAYER4; }
			}
			else if (s1 == this->trump && s2 != this->trump && s3 == this->trump && s4 == this->trump)
			{
				// some cards are of different suits
				// player 1 and player 3 and player 4 played trump
				if (c1 > c3 && c1 > c4) { player1Score++; this->lastPlayerWon = ENTITY::PLAYER1; }
				else if (c3 > c1 && c3 > c4) { player3Score++; this->lastPlayerWon = ENTITY::PLAYER3; }
				else { player4Score++; this->lastPlayerWon = ENTITY::PLAYER4; }
			}
			else if (s1 != this->trump && s2 == this->trump && s3 == this->trump && s4 == this->trump)
			{
				// some cards are of different suits
				// player 2 and player 3 and player 4 played trump
				if (c2 > c3 && c2 > c4) { player2Score++; this->lastPlayerWon = ENTITY::PLAYER2; }
				else if (c3 > c2 && c3 > c4) { player3Score++; this->lastPlayerWon = ENTITY::PLAYER3; }
				else { player4Score++; this->lastPlayerWon = ENTITY::PLAYER4; }
			}
		}
		else
		{
			// some cards are of different suit
			// no one played trump
			// player with current suit and highest card wins the game
			if (s1 == currentsuit && s2 != currentsuit && s3 != currentsuit && s4 != currentsuit)
			{
				// player1 won
				player1Score++;
				this->lastPlayerWon = ENTITY::PLAYER1;
			}
			else if (s1 != currentsuit && s2 == currentsuit && s3 != currentsuit && s4 != currentsuit)
			{
				// player2 won
				player2Score++;
				this->lastPlayerWon = ENTITY::PLAYER2;
			}
			else if (s1 != currentsuit && s2 != currentsuit && s3 == currentsuit && s4 != currentsuit)
			{
				// player3 won
				player3Score++;
				this->lastPlayerWon = ENTITY::PLAYER3;
			}
			else if (s1 != currentsuit && s2 != currentsuit && s3 != currentsuit && s4 == currentsuit)
			{
				// player 4 won
				player4Score++;
				this->lastPlayerWon = ENTITY::PLAYER4;
			}
			else if (s1 == currentsuit && s2 == currentsuit && s3 != currentsuit && s4 != currentsuit)
			{
				// player 1 and player 2 played same suit
				if (c1 > c2) { player1Score++; this->lastPlayerWon = ENTITY::PLAYER1; }
				else { player2Score++; this->lastPlayerWon = ENTITY::PLAYER2; }
			}
			else if (s1 == currentsuit && s2 != currentsuit && s3 == currentsuit && s4 != currentsuit)
			{
				// player 1 and player 3 played same suit
				if (c1 > c3) { player1Score++; this->lastPlayerWon = ENTITY::PLAYER1; }
				else { player3Score++; this->lastPlayerWon = ENTITY::PLAYER3; }
			}
			else if (s1 == currentsuit && s2 != currentsuit && s3 != currentsuit && s4 == currentsuit)
			{
				// player 1 and player 4 played same suit
				if (c1 > c4) { player1Score++; this->lastPlayerWon = ENTITY::PLAYER1; }
				else { player4Score++; this->lastPlayerWon = ENTITY::PLAYER4; }
			}
			else if (s1 != currentsuit && s2 == currentsuit && s3 == currentsuit && s4 != currentsuit)
			{
				// player 2 and player 3 played same suit
				if (c2 > c3) { player2Score++; this->lastPlayerWon = ENTITY::PLAYER2; }
				else { player3Score++; this->lastPlayerWon = ENTITY::PLAYER3; }
			}
			else if (s1 != currentsuit && s2 == currentsuit && s3 != currentsuit && s4 == currentsuit)
			{
				// player 2 and player 4 played same suit
				if (c2 > c4) { player2Score++; this->lastPlayerWon = ENTITY::PLAYER2; }
				else { player4Score++; this->lastPlayerWon = ENTITY::PLAYER4; }
			}
			else if (s1 != currentsuit && s2 != currentsuit && s3 == currentsuit && s4 == currentsuit)
			{
				// player 3 and player 4 played same suit
				if (c3 > c4) { player3Score++; this->lastPlayerWon = ENTITY::PLAYER3; }
				else { player4Score++; this->lastPlayerWon = ENTITY::PLAYER4; }
			}
			else if (s1 == currentsuit && s2 == currentsuit && s3 == currentsuit && s4 != currentsuit)
			{
				// player 1 and player 2 and player 3 played same suit
				if (c1 > c2 && c1 > c3) { player1Score++; this->lastPlayerWon = ENTITY::PLAYER1; }
				else if (c2 > c1 && c2 > c3) { player2Score++; this->lastPlayerWon = ENTITY::PLAYER2; }
				else { player3Score++; this->lastPlayerWon = ENTITY::PLAYER3; }
			}
			else if (s1 == currentsuit && s2 == currentsuit && s3 != currentsuit && s4 == currentsuit)
			{
				// player 1 and player 2 and player 4 played same suit
				if (c1 > c2 && c1 > c4) { player1Score++; this->lastPlayerWon = ENTITY::PLAYER1; }
				else if (c2 > c1 && c2 > c4) { player2Score++; this->lastPlayerWon = ENTITY::PLAYER2; }
				else { player4Score++; this->lastPlayerWon = ENTITY::PLAYER4; }
			}
			else if (s1 == currentsuit && s2 != currentsuit && s3 == currentsuit && s4 == currentsuit)
			{
				// player 1 and player 3 and player 4 played same suit
				if (c1 > c3 && c1 > c4) { player1Score++; this->lastPlayerWon = ENTITY::PLAYER1; }
				else if (c3 > c1 && c3 > c4) { player3Score++; this->lastPlayerWon = ENTITY::PLAYER3; }
				else { player4Score++; this->lastPlayerWon = ENTITY::PLAYER4; }
			}
			else if (s1 != currentsuit && s2 == currentsuit && s3 == currentsuit && s4 == currentsuit)
			{
				// player 2 and player 3 and player 4 played same suit
				if (c2 > c3 && c2 > c4) { player2Score++; this->lastPlayerWon = ENTITY::PLAYER2; }
				else if (c3 > c2 && c3 > c4) { player3Score++; this->lastPlayerWon = ENTITY::PLAYER3; }
				else { player4Score++; this->lastPlayerWon = ENTITY::PLAYER4; }
			}
		}
	}
}

/**
* Function which ensures that only one player plays at a time\n
* Function also ensures that player who won the last round plays first in the next round
* @param player1 pointer to the object of type player of player 1
* @param player2 pointer to the object of type player of player 2
* @param player3 pointer to the object of type player of player 3
* @param player4 pointer to the object of type player of player 4
*/
void RoundManager::manageTurns(Player** playerList)
{
	bool P1 = playerList[0]->getIsPlaying();
	bool P2 = playerList[1]->getIsPlaying();
	bool P3 = playerList[2]->getIsPlaying();
	bool P4 = playerList[3]->getIsPlaying();


	if (this->lastPlayerWon == ENTITY::DEFAULT)
	{
		if (P1 == false && P2 == false && P3 == false && P4 == false)
		{
			// at start player 1 will always play
			playerList[0]->setIsPlaying(true);
		}
		else if (P1 == true && P2 == false && P3 == false && P4 == false)
		{
			// when player 1 played, in next turn player 2 played
			playerList[0]->setIsPlaying(false);
			playerList[1]->setIsPlaying(true);
		}
		else if (P1 == false && P2 == true && P3 == false && P4 == false)
		{
			// when player 2 played, in next turn player 3 played
			playerList[1]->setIsPlaying(false);
			playerList[2]->setIsPlaying(true);
		}
		else if (P1 == false && P2 == false && P3 == true && P4 == false)
		{
			// when player 3 played, in next turn player 4 played
			playerList[2]->setIsPlaying(false);
			playerList[3]->setIsPlaying(true);
		}
		else if (P1 == false && P2 == false && P3 == false && P4 == true)
		{
			// when player 4 played, in next turn player 1 played
			playerList[3]->setIsPlaying(false);
			playerList[0]->setIsPlaying(true);
		}
	}
	else if (this->lastPlayerWon == ENTITY::PLAYER1)
	{
		//if Player 1 won previous round
		// player 1 will play next round
		playerList[0]->setIsPlaying(true);
		playerList[1]->setIsPlaying(false);
		playerList[2]->setIsPlaying(false);
		playerList[3]->setIsPlaying(false);
		this->lastPlayerWon = ENTITY::DEFAULT;
	}
	else if (this->lastPlayerWon == ENTITY::PLAYER2)
	{
		//if Player 2 won previous round
		//player 2 will play next round
		playerList[0]->setIsPlaying(false);
		playerList[1]->setIsPlaying(true);
		playerList[2]->setIsPlaying(false);
		playerList[3]->setIsPlaying(false);
		this->lastPlayerWon = ENTITY::DEFAULT;
	}
	else if (this->lastPlayerWon == ENTITY::PLAYER3)
	{
		//if Player 3 won previous round
		// player 3 will play next round
		playerList[0]->setIsPlaying(false);
		playerList[1]->setIsPlaying(false);
		playerList[2]->setIsPlaying(true);
		playerList[3]->setIsPlaying(false);
		this->lastPlayerWon = ENTITY::DEFAULT;
	}
	else if (this->lastPlayerWon == ENTITY::PLAYER4)
	{
		//if Player 4 won previous round
		// player 4 will play next round
		playerList[0]->setIsPlaying(false);
		playerList[1]->setIsPlaying(false);
		playerList[2]->setIsPlaying(false);
		playerList[3]->setIsPlaying(true);
		this->lastPlayerWon = ENTITY::DEFAULT;
	}
}

/**
* Destructor for class Round Manager
*/
RoundManager::~RoundManager()
{
	std::cout << "Destructor for class Round Manager called" << std::endl;
}
