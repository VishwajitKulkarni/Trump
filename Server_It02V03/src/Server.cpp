/*
 * Server.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: vishwajit
 */

#include "Server.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <iostream>
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define MAX_PLAYERS 4
//static bool isNWThreadalive = false;

/**
 * @name Server
 * @brief Constructor for Server Class
 *  Initializes SDA and SDA_Net, opens new connection and creates thread to handle connections.
 *  @param none
 *  @retval none
 */
Server::Server(Message* txFrame, Message* rxFrame) :
		TxFrame(txFrame), RxFrame(rxFrame) {
	// TODO Auto-generated constructor stub
//	TxFrame = txFrame;
	isNWThreadalive = false;
	cout<<"SocketSet created"<<endl;
	port = 2345;
	network_thread = NULL;
	initSDL();
	initSDLNet();
	initPlayerList();
	// Allocate socketeSet size (no of players plus one for server socket)
	socketSet = SDLNet_AllocSocketSet(MAX_PLAYERS + 1);
	cout<<"SocketSet created"<<endl;
	if (socketSet == NULL) {
		cout<<"Couldn't create socket set: %s\n"<<SDLNet_GetError()<<endl;
		exit(2);
	}
	createServerSock();
	cout<<endl<< "Server started successfully" << endl<<endl;
	//createNetworkThread();
}

/**
 * @name initPlayerList - Server class function
 * @brief Initializes playerlist with new null sockets.
 *
 *  @param none
 *  @retval none
 */
void Server::initPlayerList() {
	for (int i = 0; i < MAX_PLAYERS + 1; ++i) {
		playerList.push_back(new PlayerSocket);
	}
}

/**
 * @name printLocalAddress - Server class function
 * @brief Prints IP address of machine.
 *  Prints all available IPs for connection on current machine including localhost address.
 *  @param none
 *  @retval none
 */
void printLocalAddress() {
	IPaddress ipa[5];
	int availableIPs = SDLNet_GetLocalAddresses(ipa, 3);
	if (availableIPs > 0) {
		const char *hostName = SDLNet_ResolveIP(&ipa[1]);
		cout<<"Current Host Name: "<<hostName<<endl;
		cout<<"\nList of available IPs: "<<endl;
		for (int i = 0; i < availableIPs; i++) {
			int ipaddr = SDL_SwapBE32(ipa[i].host);
			cout<<"\nIP-"<<i<<" :"<<endl;
			cout<<((ipaddr>>24)&0xFF)<<"."<<((ipaddr>>16)& 0xFF)<<"."<<((ipaddr>>8)&0xFF)<<"."<<(ipaddr&0xFF)<<"."<<endl;
		}
	}

//	std::string ip = std::to_string((ipaddr >> 24) & 0xFF);
//	ip.append(".");
//	ip.append(std::to_string((ipaddr >> 16) & 0xFF));
//	ip.append(".");
//	ip.append(std::to_string((ipaddr >> 8) & 0xFF));
//	ip.append(".");
//	ip.append(std::to_string(ipaddr & 0xFF));
//	cout<<"HostIP:"<<ip<<endl;
//	return ip.c_str();
}

/**
 *  Opens socket for communication. If IP address is not resolved, program will be terminated.
 *  If connection is successful then connection information will be printed on terminal.
 *  @param none
 *  @retval none
 */
void Server::createServerSock() {

	if (SDLNet_ResolveHost(&ip, NULL, port) == -1) {
		cout<<"SDL Host resolution failed.\nExiting Program"<<endl;
		exit(3);
	}
	printLocalAddress();
//	ipaddr = SDL_SwapBE32(ip.host);
//	cout<<"\nServer IP: "<<endl;
//	cout<<(ipaddr>>24)<<"."<<((ipaddr>>16)& 0xFF)<<"."<<((ipaddr>>8)&0xFF)<<"."<<(ipaddr&0xFF)<<"."<<endl;

	serverSock = SDLNet_TCP_Open(&ip);
	if (!serverSock) {
		cout<<"SDL-Net Initialization Error."<<SDLNet_GetError()<<"\nExiting Program"<<endl;
		exit(4);
	}
	SDLNet_TCP_AddSocket(socketSet, serverSock);
}

/**
 *  Accepts new connection request by allocating new socket.
 *  If maximum limit is reached then connection will be terminated after sending 'list full' message.
 *  If socket allocation is successful then it is added to list for monitoring.
 *  @param none
 *  @retval none
 */
void Server::handleConnectionReq() {
	cout<<"[Server]: In handleConnection function"<<endl;

	int playerIndex = 0;
	for (playerIndex = 1; playerIndex < MAX_PLAYERS + 1; ++playerIndex) {
		if (playerList[playerIndex]->isSockActive==false) {
			break;
		}
	}
	if (playerIndex == MAX_PLAYERS + 1) {
		cout<<endl<<"ListFull"<<endl<<endl;
		/*If list is full, just accept connection and then terminate*/
		//TCPsocket temp = SDLNet_TCP_Accept(serverSock);
		/*TODO Probably send list full message before termination*/
		/*TODO OR create a new room*/

		TCPsocket tempClientSocket = NULL;
		tempClientSocket = SDLNet_TCP_Accept(serverSock);
		if (tempClientSocket == NULL) {
			cout<<"[Server]: Error handling new connection."<<endl;
			//TODO notify game manager and all other players before exiting
			exit(8);
		}
		std::string message = "List Full.Terminating Connection";
		SDLNet_TCP_Send(tempClientSocket,message.c_str(),sizeof(message));
		SDLNet_TCP_Close(tempClientSocket);
	}
	else {

		if(RxFrame->getMsgStatus()) {
			return;
		}
		playerList[playerIndex]->playerSock = SDLNet_TCP_Accept(serverSock);
		if (playerList[playerIndex]->playerSock == NULL) {
			cout<<"[Server]: Error handling new connection. Connection rejected"<<endl;
			//TODO notify game manager and all other players before exiting
//					exit(8);
			return;
		}

		cout<<"[Server]: Player: "<<playerIndex<<"Connected"<<endl;
//		cout<<"[Server]: Socket: "<<playerList[playerIndex]->playerSock<<endl;
		playerList[playerIndex]->playerSock;
		playerList[playerIndex]->isSockActive = true;
		playerList[playerIndex]->ip = *(SDLNet_TCP_GetPeerAddress(playerList[playerIndex]->playerSock));
		cout<<endl<<"[Server]: Total Connections: "<<playerIndex<<endl<<endl;
		TCPsocket temp = playerList[playerIndex]->playerSock;
		playerSocketList[playerIndex] = temp;
		SDLNet_TCP_AddSocket(socketSet, temp);
		cout<<"[Server]: Waiting for RxFrame to be available"<<endl;

		cout<<"[Server]: Waiting for RxFrame available to edit!"<<endl;
		RxFrame->setWhichPlayer(ENTITY::DEFAULT);
		RxFrame->setFrameType(FRAMETYPE::ADDPLAYER);
		RxFrame->setMsgStatus(MESSAGE_AVAILABLE);
//		cout<<"Calling gameManager.playerAdd()"<<endl;
//		while(1);
//		gameManager.playerAdd();
//		cout<<"Socket before exiting: "<<playerList[playerIndex]->playerSock<<endl;
	}
	cout<<"[Server]: Exiting handleIncomingConnection function"<<endl;

}

/**
 *  Handles outgoing socket activities.
 * 	Sends data in transmit buffer to Server.
 *  @param none
 *  @retval none
 */
void Server::handleOutgoingMessage(int whichPlayer) {
	cout<<"[Server]: In handle Outgoing message"<<endl;
	int frameLen = 0;
	frameLen = encodeFrame();
	if (whichPlayer > 4) {
		//broadcast
		cout<<"[Server]: Broadcast message"<<endl;
		for (int i = 0; i < 4; i++) {
			//if player is active, edit which-player field of frame and send data;
			if (playerList[i + 1]->isSockActive) {
				txBuffer[2] = static_cast<char>(i + 1);
				sendData(frameLen, i + 1);
				cout<<"[Server]: Transmitted: "<<frameLen<<" Bytes to player-"<<i+1<<"."<<endl<<endl;
			}
		}

	} else {
//		cout<<"[Server]: Attempting Transmit: "<<frameLen<<" Bytes to player-"<<whichPlayer<<"."<<endl<<endl;
		sendData(frameLen, whichPlayer);
//		if(playerList[whichPlayer]->playerSock==NULL || playerSocketList[whichPlayer]==NULL){
//			cout<<"SOCK: "<<playerList[whichPlayer]->playerSock<<" "<<playerSocketList[whichPlayer]<<endl;
////			while(1);
//		}
		cout<<"[Server]: Transmitted: "<<frameLen<<" Bytes to player-"<<whichPlayer<<"."<<endl<<endl;
	}
	// Clear flag after transmission
	TxFrame->setMsgStatus(MESSAGE_NOT_AVAILABLE);
	cout<<"[Server]: Exiting handle-outgoing function"<<endl;
}

void Server::sendData(int framelen, int whichPlayer) {
	cout<<"[Server]: In send data function"<<endl;

	int transferedBytes = 0;
//	cout<<"WhichPlayer "<<endl;
	if(playerSocketList[whichPlayer] == NULL) {
//		for(int i=0;i<=whichPlayer;i++)
		cout<<"player "<<whichPlayer<<" Socket: "<<playerSocketList[whichPlayer]<<endl;
//		cout<<"Socket is empty!"<<endl;
		while(1);
	}
	while (transferedBytes < framelen) {
		//TODO check if socket is active each time
//		transferedBytes += SDLNet_TCP_Send(playerList[whichPlayer]->playerSock,
//				txBuffer + transferedBytes, framelen - transferedBytes);
		transferedBytes += SDLNet_TCP_Send(playerSocketList[whichPlayer],
				txBuffer, framelen);
	}
	cout<<"[Server]: Exiting send data function"<<endl;

}

/**
 *  Handles incoming socket activities.
 *  If any connection is terminated then socket is closed and deleted from the monitor list.
 *  If any data is avialble then it is forwarded to game manager for further processing.
 *  @param none
 *  @retval none
 */
void Server::handleIncomingMessage(int whichClient) {
//	char receiveBuff[30];handleIncomingMessage
	cout<<"[Server]: In handleIncomingMessage"<<endl;
	if(RxFrame->getMsgStatus()) {
		cout<<"[Server]: Unable to modify RxFrame, returning."<<endl;
		return;
	}

	memset(rxBuffer, '\0', BUFFERSIZE);
	int datalen = SDLNet_TCP_Recv(playerList[whichClient]->playerSock, rxBuffer,
			BUFFERSIZE);

	cout<<"[Server]: Rec Msg length"<<datalen<<endl;
	//Check if connection is closed
	if (datalen <= 0) {

		cout<<"[Server]: Client-"<<whichClient<<" disconnected."<<endl;
		SDLNet_TCP_DelSocket(socketSet, playerList[whichClient]->playerSock);
		SDLNet_TCP_Close(playerList[whichClient]->playerSock);
		playerList[whichClient]->isSockActive = false;
		playerList[whichClient]->playerSock = NULL;

		/*Notify game manager*/
//		RxFrame->flushall();
		RxFrame->setWhichPlayer(static_cast<ENTITY>(whichClient));
		RxFrame->setFrameType(FRAMETYPE::LEAVEGAME);
		RxFrame->setMsgStatus(MESSAGE_AVAILABLE);
//		gameManager->handleMessage();
//		cout<<"Calling gameManager.handleMessage() for exit request"<<endl;
//memset(rxBuffer,'\0',BUFFERSIZE);
	} else {
		cout<<"[Server]: something is received"<<endl;
		//fill data to appropriate player buffer
		//TOD eventually SOF should be at 0th location. THINK!
		for(int i=0;i<datalen;i++)
		printf("%02x ",rxBuffer[i]);
		playerList[whichClient]->fillBuffer(rxBuffer,datalen);
		int SOFIndex = playerList[whichClient]->isSOFReceived();
		if(SOFIndex>=0) {
			cout<<"[Server]: SOF Received: "<< SOFIndex<<endl;
			int EOFIndex = playerList[whichClient]->isEOFReceived();
			if(EOFIndex>SOFIndex) {
				//wait until game manager processes previous data
				cout<<"[Server]: EOF Received: "<<EOFIndex<<endl;
				if(RxFrame->getMsgStatus()) {
					return;
				}
//				while(RxFrame->getMsgStatus());
				cout<<"[Server]: RXFRAME Free to be modified"<<endl;
				// verify data length is correct by checking sof-index+datalenght = EOF
				int frameLength = *(playerList[whichClient]->getRxBufferPtr()+SOFIndex+1);
//				cout<<"FrameLength::"<<frameLength<<endl;
//				cout<<"SOF INDEX: "<<SOFIndex<<endl;
//				cout<<"EOF INDEX: "<<EOFIndex<<endl;
				if(SOFIndex+frameLength+1 == EOFIndex) {
					//TODO boolean decode Frame rather than void
//					cout<<"Going to decode the frame "<<endl;
					decodeFrame(playerList[whichClient]->getRxBufferPtr()+SOFIndex,frameLength);
					//shift data in buffer and  change buffer-index accordingly
					playerList[whichClient]->shiftBufferData(SOFIndex,EOFIndex);
					//flush buffer
//					char *ptr= playerList[whichClient]->getRxBufferPtr()+SOFIndex;
					//					playerList[whichClient]->flushBuffer(ptr, frameLength);
//					cout<<"[Server]: Calling gameManager.handleMessage()"<<endl;
//					gameManager->handleMessage();
				}
				else {
					cout<<"[Server]: Wrong EOF!! Flushing data."<<endl;
					//TODO flushData
				}
			}
		}

//		receiveBuff[datalen + 1] = '\0'; //null terminate
//		cout<<"Received bytes: "<<datalen<<endl<<"Received message: "<<receiveBuff<<endl;
//		memset(rxBuffer, 0, BUFFERSIZE);
	}
	cout<<"[Server]: Exiting handle-incoming messages function"<<endl;
}
/**
 *  Thread activities are handled by this function.
 *  Constantly checks for incoming data or transmission requests and handles if any.
 *  Thread can be terminated by setting isNWThreadalive flag to false.
 *  @param none
 *  @retval none
 */
void Server::handleNetworkThreadCallback() {
//	cout<<"Network THread Success!"<<endl;
//	cout<<"Running Thread. Thread ID:"<<SDL_ThreadID() <<endl;
	int pending_requests = 0;
//	isNWThreadalive = true;
//	cout<<"Server thread"<<endl;
//	while(this->isNWThreadalive) {

//		cout<<"Checking for Client Request."<<endl;
	pending_requests = SDLNet_CheckSockets(socketSet, 0);
	if (pending_requests > 0) {
		if (SDLNet_SocketReady(serverSock)) {
			cout<<"Checking requests"<<endl;
			handleConnectionReq();
		}
//			cout<<"Checking for messages."<<endl;
		for (int i = 0; i < MAX_PLAYERS + 1; i++) {
			if (playerList[i]->isSockActive) {
				if (SDLNet_SocketReady(playerList[i]->playerSock)) {
					cout<<"Message received from client-"<<i<<"."<<endl;
					handleIncomingMessage(i);
				}
			}
		}
	}
	if (TxFrame->getMsgStatus()) {
		int whichPlayer = static_cast<int>(TxFrame->getWhichPlayer());
		handleOutgoingMessage(whichPlayer);
	}
//}
//	cout<<"Exiting handlenetworkThreadCallback function"<<endl;
}
/**
 *  Wrapper function for handleNetworkThreadCallback function.
 *  Created as thread creation requires static functions.
 *  @param void* data
 *  @retval none
 */
static int networkThreadCallback(void* data) {
//	cout<<"in Network THread Callback."<<endl;
	((Server*) data)->handleNetworkThreadCallback();
	cout<<"[Server]: Exiting networkThreadCallback function"<<endl;
	return 0;
}

/**
 *  Creates thread to handle network traffic
 *  @param none
 *  @retval none
 */
void Server::createNetworkThread() {
	network_thread = SDL_CreateThread(networkThreadCallback, "NetworkThread",
			this);
	if (!network_thread) {
		cout<<"SDL_CreateThread: "<< SDL_GetError()<<endl;
		exit(7);
	}

	/*If sucess start network thread*/
//isNWThreadalive = true;
	cout<<"[Server]: Server Network THread created Successfully!"<<endl;
}

/**
 *  SDL Initialization function.
 *  @param none
 *  @retval none
 */
void Server::initSDL() {
	if (SDL_Init(0) == -1) {
		cout<< "SDL Initialization Error.\nExiting Program" << endl;
		exit(0);
	}
}

/**
 *  SDL_net Initialization function.
 *  @param none
 *  @retval none
 */
void Server::initSDLNet() {
	if (SDLNet_Init() == -1) {
		cout<< "SDL-Net Initialization Error.\nExiting Program" << endl;
		exit(0);
	}
}

int Server::encodeFrame() {
	cout<<"In encode Frame function"<<endl;
	memset(txBuffer, '\0', BUFFERSIZE);
	int currentCase = 0;
	uint8_t frameLen = TxFrame->getMsgLength()+8;
//	cout<<"Calculated frameLength = "<<frameLen<<endl;
	uint8_t i = 0;
	while (i < frameLen) {
		switch (currentCase) {
			case 0:
			//insert SOF
//			cout<<endl<<"case: "<<currentCase<<endl;
			txBuffer[i] = static_cast<char>(FRAME_SOF);
			currentCase++;
			i++;
			break;

			case 1:
			//insert frame-length
//			cout<<endl<<"case: "<<currentCase<<endl;
			txBuffer[i] = 0xFF&(frameLen-2);
			currentCase++;
			i++;
			break;

			case 2:
			//insert whichplayer
//			cout<<endl<<"case: "<<currentCase<<endl;
			txBuffer[i] = static_cast<char>(TxFrame->getWhichPlayer());
			currentCase++;
			i++;
			break;

			case 3:
			//insert frame-type
//			cout<<endl<<"case: "<<currentCase<<endl;
			txBuffer[i] = static_cast<char>(TxFrame->getFrameType());
			currentCase++;
			i++;
			break;

			case 4:
			//insert data-type
//			cout<<endl<<"case: "<<currentCase<<endl;

			txBuffer[i] = static_cast<char>(TxFrame->getDataType());
			currentCase++;
			i++;
			break;

			case 5:
			//insert message-length
			txBuffer[i] = static_cast<char>(TxFrame->getMsgLength());
			currentCase++;
			i++;
			break;

			case 6:
			//insert data
			char *dataPtr;
			dataPtr = TxFrame->getMsgBuffer();
			for (int j = 0; j < TxFrame->getMsgLength(); j++) {
				txBuffer[i] = *dataPtr;
				dataPtr++;
				i++;

			}
			currentCase++;
			break;

			case 7:
			//insert CRC
			//TODO Calculate CRC
			txBuffer[i] = 0;
			currentCase++;
			i++;
			break;

			case 8:
			//insert EOF
			txBuffer[i] = FRAME_EOF;

//			cout<<endl<<"case: "<<currentCase<<endl;
//			printf("%02x ", txBuffer[i]);
//			cout<<txBuffer[i]<<endl;

			currentCase++;
			i++;
//			cout<<"Framelenght = "<<i-1<<endl;
			break;

			default:
			cout<<"case: "<<currentCase<<endl;
			cout<<"Something wrong with frame decoding"<<endl;
			i++;
		}
	}
	cout<<"[Server]:Exiting encode frame function"<<endl;
//	for(int i =0; i<frameLen;i++) {
//		printf("%02x",txBuffer[i]);
//	}
	return static_cast<int>(frameLen);
}

void Server::decodeFrame(char *ptr, int frameLen) {
	cout<<"[Server]:In decode frame function"<<endl;
	int currentCase = 0;
	int i = 0;
	ptr += 2; //TODO this is cheap solution to neglect SOF and frameLen. IMPROVE
	while (i < frameLen) {
		switch (currentCase) {
			case 0: {
				//
				cout<<"case: "<<currentCase<<" i: "<<i<<endl;
				printf("%02x",*ptr);
				cout<<endl;
				RxFrame->flushall();
				RxFrame->setWhichPlayer(static_cast<ENTITY>(*ptr));
				ptr++;
				currentCase++;
				i++;
			}
			break;

			case 1:
			{
				cout<<"case: "<<currentCase<<" i: "<<i<<endl;
				printf("%02x",*ptr);
				cout<<endl;
				RxFrame->setFrameType(static_cast<FRAMETYPE>(*ptr));
				ptr++;
				currentCase++;
				i++;}
			break;

			case 2:
			{
				cout<<"case: "<<currentCase<<" i: "<<i<<endl;
				printf("%02x",*ptr);
				cout<<endl;
				RxFrame->setDataType(static_cast<DATATYPE>(*ptr));
				ptr++;
				currentCase++;
				i++;
			}
			break;

			case 3:
			{
				cout<<"case: "<<currentCase<<" i: "<<i<<endl;
				printf(" %02x",*ptr);
				cout<<endl;
				RxFrame->setMsgLength(static_cast<int>(*ptr));
				ptr++;
				currentCase++;
				i++;
			}
			break;

			case 4:
			{
				cout<<"case: "<<currentCase<<" i: "<<i<<endl;
				printf(" %02x",*ptr);

				if(RxFrame->getMsgLength()>0 && RxFrame->getMsgLength()<frameLen ) {
					RxFrame->setMsgBuffer(ptr, RxFrame->getMsgLength());
					printf("ML: %02x", RxFrame->getMsgLength());
					printf(" %02x",*(ptr+1));
					printf(" %02x",*(ptr+2));
					printf(" %02x",*(ptr+3));
					printf(" %02x",*(ptr+4));
					ptr += RxFrame->getMsgLength();
					currentCase++;
					i+=RxFrame->getMsgLength();
				}
				else {
					currentCase =0;
					RxFrame->flushall();
					i++;
					ptr++;
				}
				cout<<endl;
			}
			break;

			case 5:
			{
				//TODO CRC
				cout<<"case: "<<currentCase<<" i: "<<i<<endl;
				printf(" %20x",*ptr);
				cout<<endl;

				ptr++;
				currentCase++;
				i++;
			}
			break;

			case 6:
			{
				cout<<"case: "<<currentCase<<" i: "<<i<<endl;
				printf("% 20x",*ptr);
				cout<<endl;
				if(*ptr == FRAME_EOF)
				{
//					while(RxFrame->getMsgStatus());
					RxFrame->setMsgStatus(MESSAGE_AVAILABLE);
					cout<<"[Server]: EOF Recieved, Rx Flag is True"<<endl;
				}
				else {
					cout<<endl<<"!!FALSE EOF MATCH!!"<<endl;
//					RxFrame->flushall();
				}
				i++;
				currentCase =0;
			}
			break;

			default:
			{
				cout<<"case: "<<currentCase<<" i: "<<i<<endl;
				cout<<"[Server]:Something wrong with frame decoding"<<endl;
				i++;
				currentCase =0;
			}
			break;
		}
	}
	cout<<"[Server]:Exiting decode frame function"<<endl;
}
/**
 *  Destructor for Server class.
 *  Enusres thread has been terminated before object gets deleted.
 *  @param none
 *  @retval none
 */
Server::~Server() {
	cout<<"In server destructor function"<<endl;
//	SDL_KillThread(network_thread);
	isNWThreadalive = false;
	SDL_WaitThread(network_thread, NULL);
	// TODO Auto-generated destructor stub
}

