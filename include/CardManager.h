///\file
/*!
*  \details   Implementation of Trump game
*  \author    Shubham Yadav (s1911996) (s.yadav@student.utwente.nl)
*  \version   1.2
*  \date      Created on : 23 November 2017\n
			  Last Modified on : 12 December 2017
*/

#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H

#include "Card.h"
#include "TrumpMisc.h"

class CardManager
{
private:
	Card *allCards[52]; /**< array of pointer of objects of type Card*/
	void shuffleCards(void); /**< private function used to shuffle the cards when class is instantiated*/
public:
	CardManager(void);
	Card** getshuffledCards(void);
	void toString(void);
	~CardManager(void);
};


#endif // !CARD_MANAGER_H




