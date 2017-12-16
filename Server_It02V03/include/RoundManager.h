///\file
/*!
*  \details     Implementation of Trump game
*  \author    Shubham Yadav (s.yadav@student.utwente.nl)
*  \version   1.0
*  \date      23 November 2017
*/

#ifndef ROUND_MANAGER_H
#define ROUND_MANAGER_H

#include "TrumpMisc.h"
#include "Card.h"
#include "Player.h"

class RoundManager
{
private:
	int scoreTeamA; /*!< score of team A*/
	int scoreTeamB; /*!< score of team B*/
	int player1Score; /*!< score of player 1*/
	int player2Score; /*!< score of player 2*/
	int player3Score; /*!< score of player 3*/
	int player4Score; /*!< score of player 4*/
	ENTITY lastPlayerWon; /*!< player who won the last round*/
	SUITS trump; /*!< trump suit*/
	int roundCount; /*!< round number*/
public:
	RoundManager(SUITS);
	void increaseRoundCount(void);
	SUITS getTrump(void);
	void setTrump(SUITS);
	int getRoundCount(void);
	int getScoreTeamA(void);
	int getScoreTeamB(void);
	ENTITY getLastPlayerWon(void);
	void checkRound(Card**, SUITS);
	void manageTurns(Player**);
	~RoundManager();
};

#endif // !ROUND_MANAGER_H



