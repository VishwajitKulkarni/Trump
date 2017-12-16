/*
 * PlayerSocket.h
 *
 *  Created on: Dec 6, 2017
 *      Author: vishwajit
 */

#ifndef INCLUDE_PLAYERSOCKET_H_
#define INCLUDE_PLAYERSOCKET_H_
#include <SDL2/SDL_net.h>

#include "ServerMisc.h"

class PlayerSocket {
	char rxBuffer[BUFFERSIZE];
	uint8_t rxBufferIndex;
public:
	TCPsocket playerSock;
	bool isSockActive;
	_PlayerNumber playerID;
	IPaddress ip;
	void shiftBufferData(int startIndex, int endIndex);
	int isSOFReceived();
	int isEOFReceived();
	void fillBuffer(char *dataPtr, int datalen);
	void flushBuffer(char *ptr, int len);
	char* getRxBufferPtr();
	PlayerSocket();
	virtual ~PlayerSocket();
};

#endif /* INCLUDE_PLAYERSOCKET_H_ */
