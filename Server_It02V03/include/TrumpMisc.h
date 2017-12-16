///\file
/*
*
*  \details   Implementation of Trump game
*  \author    Shubham Yadav (s.yadav@student.utwente.nl)
*  \version   2.0
*  \date      23 November 2017
*
*/

#ifndef TRUMPMISC_H
#define TRUMPMISC_H

/*!
*
* This is a enum class of Suits
*
*/
enum class SUITS : int
{
	HEARTS, /**< Hearts*/
	DIAMONDS, /**< Diamonds*/
	CLUBS, /**< Clubs*/
	SPADES, /**< Spades*/
	DEFAULT, /**< Default value*/
};

/*!
*
* This is a enum class of all the entities used for communication and normal execution
*
*/
enum class ENTITY : int
{
	SERVER, /**< Message by/for Server*/
	PLAYER1, /**< Message by/for Player 1*/
	PLAYER2, /**< Message by/for Player 2*/
	PLAYER3, /**< Message by/for Player 3*/
	PLAYER4, /**< Message by/for Player 4*/
	BROADCAST, /**< Message for Broadcast by Server*/
	DEFAULT, /**< Default value*/
};


/*!
*
* This is a enum class of teams
*
*/
enum class TEAM : int
{
	TEAMA, /**< Team A*/
	TEAMB, /**< Team B*/
	DEFAULT, /**< Default value*/
};

/*!
*
* This is a enum class of message frame types
*
*/
enum class FRAMETYPE : int
{
	JOINREQUEST,//
	SETTRUMP,//
	CARDPLAYED,//
	LEAVEGAME,//
	ACKJOINREQ,//
	FIRST5CARDS,//
	TRUMPIS,//
	TURNTOPLAY,//
	REMAININGCARDS,//
	BROADCASTTRUMP,//
	BROADCASTMOVE,//
	BROADCASTRESULT,//
	BROADCASTWINNER,//
	BROADCASTGAMEOVER,//
	BROADCASTPLAYERSINFO,//
	ADDPLAYER,
	DEFAULT,//
};

/*!
*
* This is a enum class of datatypes
*
*/
enum class DATATYPE : int
{
	CHARACTER,
	DEFAULT,
};

#endif // !TRUMPMISC_H
