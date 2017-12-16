/*
 * PlayerSocket.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: vishwajit
 */

#include "PlayerSocket.h"
#include <iostream>
/**
 * Constructor for PlayerSocket class. Initializes all variables.
 * @param none
 * @retval  none
 */
PlayerSocket::PlayerSocket() {
	// TODO Auto-generated constructor stub
	isSockActive = false;
	playerID = _INVALIDPLAYER;
	playerSock = NULL;
//	ip = 0;
	memset(rxBuffer, '\0', BUFFERSIZE);
	rxBufferIndex = 0;
}

void PlayerSocket::fillBuffer(char *dataPtr, int datalen) {
	std::cout << "[Server]: Received data in fillbuffer" << std::endl;
	std::cout << "[Server]: datalen" << datalen << std::endl;
	for (int i = 0; i < datalen; i++) {
		rxBuffer[rxBufferIndex] = *dataPtr;
//		printf("i:%d %02x ", i, rxBuffer[rxBufferIndex]);
//		std::cout << "" << std::endl;
		rxBufferIndex++;
		dataPtr++;
	}
}

void PlayerSocket::shiftBufferData(int startIndex, int endIndex) {
//	for (int i = 0; i < (rxBufferIndex - endIndex); i++) {
//		rxBuffer[startIndex + i] = rxBuffer[endIndex + i];
//	}
//	rxBufferIndex -= (startIndex - endIndex);
//	char* tempPtr = rxBuffer + (rxBufferIndex - endIndex) + startIndex;
//	memset(tempPtr, '\0', BUFFERSIZE - rxBufferIndex);
	rxBufferIndex -= (endIndex-startIndex+1);
}

int PlayerSocket::isSOFReceived() {
	for (int i = 0; i < BUFFERSIZE; i++) {
		if (rxBuffer[i] == FRAME_SOF)
			return i;
	}
	return -1;
}
int PlayerSocket::isEOFReceived() {
	for (int i = 0; i < BUFFERSIZE; i++) {
		if (rxBuffer[i] == FRAME_EOF)
			return i;
	}
	return -1;
}

void PlayerSocket::flushBuffer(char *ptr, int len) {
	memset(ptr, '\0', len);
}
char* PlayerSocket::getRxBufferPtr() {
	return rxBuffer;
}
/**
 * Destructor for PlayerSocket class.
 * @param none
 * @retval  none
 */
PlayerSocket::~PlayerSocket() {
	// TODO Auto-generated destructor stub
}

