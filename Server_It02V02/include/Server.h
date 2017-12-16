/*
 * Server.h
 *
 *  Created on: Dec 6, 2017
 *      Author: vishwajit
 */

#ifndef INCLUDE_SERVER_H_
#define INCLUDE_SERVER_H_

#include <iostream>
#include <SDL2/SDL_net.h>
#include <vector>
#include "GameManager.h"
#include "PlayerSocket.h"
#include "ServerMisc.h"

class Server {
	Message *TxFrame, *RxFrame;
//	GameManager gameManager;
	uint16_t port;
	uint32_t ipaddr;
	IPaddress ip, *remoteip;
	TCPsocket clientSock, serverSock;
	std::vector<PlayerSocket *> playerList;
	TCPsocket playerSocketList[5];
	SDLNet_SocketSet socketSet;
	SDL_Thread *network_thread;
	char txBuffer[BUFFERSIZE], rxBuffer[BUFFERSIZE];
	bool isNWThreadalive;
//	static int networkThreadCallback(void *data);
	void initSDL();
	void initSDLNet();
	void createServerSock();

	void initPlayerList();
	void handleConnectionReq();
	void handleIncomingMessage(int whichClient);
	void handleOutgoingMessage(int whichPlayer);
	void sendData(int framelen, int whichPlayer);
public:
	void createNetworkThread();
	void handleNetworkThreadCallback();
	Server(Message* txFrame, Message* rxFrame);
	virtual ~Server();
	void decodeFrame(char *ptr, int frameLen);
	int encodeFrame();

};

#endif /* INCLUDE_SERVER_H_ */

