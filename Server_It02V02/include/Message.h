///\file
/*!
*  \details   Implementation of Trump game
*  \author    Shubham Yadav (s.yadav@student.utwente.nl)
*  \version   1.0
*  \date      23 November 2017
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>
#include "TrumpMisc.h"

#define BUFFERLENGTH 256

class Message
{
private:
	ENTITY whichPlayer;
	FRAMETYPE frameType;
	DATATYPE dataType;
	int msgLength;
	char msgBuffer[BUFFERLENGTH];
	bool available;
public:
	Message();

	void setMsgStatus(bool);
	bool getMsgStatus(void);

	void flushBuffer(void);
	void flushall(void);

	void setWhichPlayer(ENTITY);
	ENTITY getWhichPlayer(void);

	void setFrameType(FRAMETYPE);
	FRAMETYPE getFrameType(void);

	void setDataType(DATATYPE);
	DATATYPE getDataType(void);

	void setMsgLength(int);
	int getMsgLength(void);

	void setMsgBuffer(char*, int);
	char* getMsgBuffer(void);

	~Message();
};

#endif // !MESSAGE_H