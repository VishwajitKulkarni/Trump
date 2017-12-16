///\file
/*!
*  \details   Implementation of Trump game
*  \author    Shubham Yadav (s1911996) (s.yadav@student.utwente.nl)
*  \version   1.2
*  \date      Created on : 23 November 2017\n
			  Last Modified on : 12 December 2017
*/

#ifndef CARD_H
#define CARD_H

#include "TrumpMisc.h"

class Card
{
private:
	SUITS suit; /**< Attribute suit of the card*/
	int cardNumber; /**< Attribute card number of the card*/
	bool cardValid; /**< True when card is available in game\n False when card is won by any team and thus not available
							in game*/
public: 
	Card(); 
	void setSuit(SUITS); 
	SUITS getSuit(void);
	void setCardNumber(int); 
	int getCardNumber(void);
	void setCardValidity(bool); 
	bool getCardValidity(void);
	void toString(void); 
	~Card(); 
};

#endif
