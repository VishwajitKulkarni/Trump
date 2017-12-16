///\file
/*!
*  \details   Implementation of Trump game
*  \author    Shubham Yadav (s1911996) (s.yadav@student.utwente.nl)
*  \version   1.2
*  \date      Created on : 23 November 2017\n
			  Last Modified on : 12 December 2017
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Card.h"

class Player
{
private:
	ENTITY playerID; /*!< player ID*/
	std::string playerName;/*!< player name*/
	Card *currentCards[13];/*!< array of pointers of cards alloted to a player*/
	TEAM team; /*!< team in which a player belongs*/
	bool isPlaying; /*!< whether player is playing or not*/
	bool isActive; /*!< whether player is active on network or not*/
public:
	Player(bool);
	ENTITY getPlayerID(void);
	void setPlayerID(ENTITY);
	std::string getPlayername(void);
	void setPlayername(std::string);
	void setTeam(TEAM);
	TEAM getTeam(void);
	void set5Cards(Card**);
	void setRestCards(void);
	Card** getCards(void);
	void movePlayed(Card*);
	bool getIsPlaying(void);
	void setIsPlaying(bool);
	void setIsActive(bool);
	bool getIsActive(void);
	void toString(void);
	~Player();
};

#endif // !PLAYER_H