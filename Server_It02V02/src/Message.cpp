///\file
/*
*  Author    Shubham Yadav (s.yadav@student.utwente.nl)
*  Version   1.0
*  Date      23 November 2017
*  Brief     Implementation of Trump game
*/

#include <stdio.h>
#include <string.h>
#include "Message.h"

/**
* Constructor for message class with no input parameters
* It sets all the class fields to their default value
*/
Message::Message()
{
	this->whichPlayer = ENTITY::DEFAULT;
	this->frameType = FRAMETYPE::DEFAULT;
	this->dataType = DATATYPE::DEFAULT;
	this->msgLength = 0;
	memset(msgBuffer,'\0',BUFFERLENGTH);
	this->available = false;
}

/**
* Function to set the status of shared message
* @param stat boolean value which has different meaning for Tx message and Rx message.
* For Tx message, true means data in message fields are valid and can be transmitted over network
* and false means message can be edited. For Rx message, true means message is valid and can be
* processed and false means the message is already read and can be edited for new messages.
*/
void Message::setMsgStatus(bool stat)
{
	this->available = stat;
}

/**
* Function to get the status of shared message
* @return boolean value representing the status of shared message
*/
bool Message::getMsgStatus(void)
{
	return this->available;
}

/**
* Function to flush the message buffer
*/
void Message::flushBuffer(void)
{
	this->available = false;
	this->msgLength = 0;
	memset(msgBuffer,'\0',BUFFERLENGTH);
}

/**
* Function to flush the complete message frame
*/
void Message::flushall(void)
{
	this->whichPlayer = ENTITY::DEFAULT;
	this->frameType = FRAMETYPE::DEFAULT;
	this->dataType = DATATYPE::DEFAULT;
	this->msgLength = 0;
	memset(msgBuffer,'\0',BUFFERLENGTH);
	this->available = false;
}

/**
* Function to set the player who has sent the message or to whom the message is intented for TX
* @param player enum ENTITY type variable representing the sender/receiver of message
*/
void Message::setWhichPlayer(ENTITY player)
{
	this->whichPlayer = player;
}

/**
* Function to get the sender/receiver of the message
* @return enum ENTITY for the sender/receiver
*/
ENTITY Message::getWhichPlayer(void)
{
	return this->whichPlayer;
}

/**
* Function to set the type of message
* @param type enum FRAMETYPE variable representing the message type
*/
void Message::setFrameType(FRAMETYPE type)
{
	this->frameType = type;
}

/**
* Function to get the type of message
* @return enum FRAMETYPE for message type
*/
FRAMETYPE Message::getFrameType(void)
{
	return this->frameType;
}

/**
* Function to set the data type of message to be sent
* @param datatype enum DATATYPE variable representing the data type of message
*/
void Message::setDataType(DATATYPE datatype)
{
	this->dataType = datatype;
}

/**
* Function to get the datatype of message
* @return data type of message
*/
DATATYPE Message::getDataType(void)
{
	return this->dataType;
}

/**
* Function to set the length of message to be transmitted
* @param len length of message
*/
void Message::setMsgLength(int len)
{
	this->msgLength = len;
}

/**
* Function to get the length of message
* @return integer type length of message
*/
int Message::getMsgLength(void)
{
	return this->msgLength;
}

/**
* Function to set the message into the message buffer
* @param temp pointer to the array of characters representing message
* @param len length of valid message
*/
void Message::setMsgBuffer(char* temp, int len)
{
	flushBuffer();
	setMsgLength(len);
	for (int i = 0; i < len; ++i)
	{
		this->msgBuffer[i] = temp[i];
	}
}

/**
* Function to get the message buffer
* @return pointer to the array of message buffer
*/
char* Message::getMsgBuffer(void)
{
	return this->msgBuffer;
}

/**
* Destructor for class Message
*/
Message::~Message()
{
	std::cout << "Destructor for class Message called" << std::endl;
}