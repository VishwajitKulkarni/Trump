///\file
/*
 *  Author    Shubham Yadav (s.yadav@student.utwente.nl)
 *  Version   1.0
 *  Date      23 November 2017
 *  Brief     Implementation of Trump game
 */

#include <iostream>
#include <memory>
#include "GameManager.h"
#include "CommandLineUserInterface.h"
#include "Message.h"

/**
 * Constructor with 1 input parameters
 * @param ipaddress server IP to be displayed on CLI
 */
GameManager::GameManager(Message* txBuffptr, Message* rxBuffptr) {
	//initial variable assignemnt
	playerCount = 0;
	canPlayMove = false;
	currentSuit = SUITS::DEFAULT;
	chanceCount = 52;
	isThreadAlive = false;
	//setting pointer for shared object of transmission messages
	this->txBuffer = txBuffptr;
	this->rxBuffer = rxBuffptr;

	//initializing object for printing on CLI
	printer = new CommandLineUserInterface();

	//If this message is displayed, it means server creation is successfull
	printer->printString(
			"------------> Server is now up and running <-----------\n\n");

	//Welcome message
	printer->printString(
			"------------> Welcome to the game of Trump <-----------\n");
	printer->printString(
			"--> This game is created as a part of an assignment <--\n");
	printer->printString(
			"--------> This is the server end of the game <---------\n");
	printer->printString(
			"--------------> Hope you will enjoy it <---------------\n\n");

	//IP address and port number for clients
	printer->printString(
			"To play this game, please run the client application and\nenter the Server IP Address\n\n");

	printer->printString("Waiting for players to join...\n");

	//initializing object for managing cards
	//this will also result into creation of shuffled cards
	cardManager = new CardManager();

	//creating 4 empty seats for players to join
	playerList[0] = new Player(false);
	playerList[1] = new Player(false);
	playerList[2] = new Player(false);
	playerList[3] = new Player(false);

	// creating objects of class Card to keep a track of cards played by different players
	cardPlayed[0] = new Card();
	cardPlayed[1] = new Card();
	cardPlayed[2] = new Card();
	cardPlayed[3] = new Card();
}

void GameManager::handleNetworkThreadCallback() {
	this->isThreadAlive = true;

	while (this->isThreadAlive) {
//		std::cout<<"CLient thread"<<std::endl;
		if (rxBuffer->getMsgStatus()) {
			this->handleMessage();
		}
	}
}

/**
 *  Wrapper function for handleNetworkThreadCallback function.
 *  Created as thread creation requires static functions.
 *  @param void* data
 *  @retval none
 */
static int networkThreadCallback(void* data) {
//	cout<<"in Network THread Callback."<<endl;
	((GameManager*) data)->handleNetworkThreadCallback();
	std::cout << "Exiting networkThreadCallback function" << std::endl;
	return 0;
}

/**
 *  Creates thread to handle network traffic
 *  @param none
 *  @retval none
 */
void GameManager::createNetworkThread() {
	network_thread = SDL_CreateThread(networkThreadCallback, "NetworkThread",
			this);
	if (!network_thread) {
		std::cout << "SDL_CreateThread: " << SDL_GetError() << std::endl;
		exit(7);
	}

	/*If sucess start network thread*/
	//isNWThreadalive = true;
	std::cout << "Network THread created Successfully!" << std::endl;
}

/**
 * Function to add a player and allot ID when physical connection is established
 */

void GameManager::playerAdd(void) {
//	std::cout << "In PlayerAdd function" << std::endl;
	int i = 0;
	for (i = 0; i < 4; i++) {
		//checking if player is active or not
		if (!playerList[i]->getIsActive()) {
			break;
		}
//		playerList[i]->setIsActive(true);
//		playerList[i]->setPlayerID(static_cast<ENTITY>(i + 1));
//		playerList[i]->setTeam(static_cast<TEAM>(i % 2));
//		playerList[i]->set5Cards(cardManager->getshuffledCards());
//		std::cout << "[MANAGE]: Sending ACK message "<<i << std::endl;
//
//		sendAckMessage(playerList[i]->getPlayerID(), playerList[i]->getTeam());
	}

	// 'i' players have joined uptill now
	// allot player seat, player ID and team and cards
	playerList[i]->setIsActive(true);
	playerList[i]->setPlayerID(static_cast<ENTITY>(i + 1));
	playerList[i]->setTeam(static_cast<TEAM>(i % 2));
	playerList[i]->set5Cards(cardManager->getshuffledCards());
	std::cout << "[MANAGE]: Sending ACK message" << std::endl;
	//sending acknowledgement with player ID and team
	sendAckMessage(playerList[i]->getPlayerID(), playerList[i]->getTeam());
}

/**
 * Function to handle the message received from transmission
 */
void GameManager::handleMessage(void) {
	printer->printString(
			"\n[MANAGE]: New message is received on network. Request is being handled.\n");

	switch (rxBuffer->getFrameType()) {
	case FRAMETYPE::ADDPLAYER: {
		playerAdd();
		break;
	}
	case FRAMETYPE::LEAVEGAME: {

		//player left the game or exited the GUI window
		//inform all players about leaving the game
		broadcastGameOver(rxBuffer->getMsgBuffer()[0]);

		//Display game leaving and exiting messages on screen
		printer->printString(
				"\n[MANAGE]: "
						+ playerList[static_cast<int>(rxBuffer->getMsgBuffer()[0]
								- '1')]->getPlayername()
						+ "has left the game. Game will quit now..." + "\n");
		printer->printString("\n\n[MANAGE]: Press enter to exit...\n");
		std::cin.get();
//			rxBuffer->setMsgStatus(false);
		exit(0);
		break;
	}
	case FRAMETYPE::JOINREQUEST: {
		// name received
		printer->printString("[MANAGE]: IN JOINREQUEST\n");
		std::cout << "[MANAGE]: Whichplayer = "
				<< static_cast<int>(rxBuffer->getWhichPlayer()) << std::endl;
//		std::cout<<rxBuffer->getWhichPlayer();
		playerList[static_cast<int>(rxBuffer->getWhichPlayer()) - 1]->setPlayername(
				rxBuffer->getMsgBuffer());

		printer->playerJoinWith5Cards(playerList[playerCount]);
		playerCount++;
		printer->printString("[MANAGE]: EXITING JOINREQUEST\n");
//			rxBuffer->setMsgStatus(false);
		break;
	}
	case FRAMETYPE::TRUMPIS: {
		//any player can set trump
		//initializing object for keeping track of rounds and trump
		roundManager = new RoundManager(
				static_cast<SUITS>((rxBuffer->getMsgBuffer()[0]) - '0'));

//			rxBuffer->setMsgStatus(false);

		//if trump is set, braodcast trump to all players
		broadcastTrump();

		//after broadcasting trump, send remaining cards to players
		sendRemainingCards();

		//display the updated status of all players
		playerList[0]->toString();
		playerList[1]->toString();
		playerList[2]->toString();
		playerList[3]->toString();

		//now player can start playing moves
		canPlayMove = true;
		break;
	}
	case FRAMETYPE::CARDPLAYED: {
		rxBuffer->setMsgStatus(false);

		//save card for future
		// this card will be checked with other cards for result of rounds
		SUITS tempSuit = static_cast<SUITS>(rxBuffer->getMsgBuffer()[0] - '0');
		int tempCardNumber = ((rxBuffer->getMsgBuffer()[1] - '0') * 10)
				+ (rxBuffer->getMsgBuffer()[2] - '0');
		int tempPlayer = static_cast<int>(rxBuffer->getWhichPlayer()) - 1;
		cardPlayed[tempPlayer]->setSuit(tempSuit);
		cardPlayed[tempPlayer]->setCardNumber(tempCardNumber);

		//setting the current suit of game
		if (chanceCount % 4 == 0) {
			currentSuit = tempSuit;
		}

		//setting the validity of card played to false
		playerList[tempPlayer]->movePlayed(cardPlayed[tempPlayer]);

		//displaying the moves played by player
		printer->displayPlayerMoves(playerList[tempPlayer],
				cardPlayed[tempPlayer]);

		//move of the player will be broadcasted
		broadcastMove(tempPlayer, tempSuit, tempCardNumber);

		//we will also check if all players have played a round for calculating the result
		if (chanceCount % 4 == 0 && chanceCount < 52) {
			//check for the result
			roundManager->checkRound(cardPlayed, currentSuit);

			//display the result on CLI
			printer->printString(
					"\n[MANAGE]: "
							+ playerList[static_cast<int>(roundManager->getLastPlayerWon())
									- 1]->getPlayername()
							+ " has won the round "
							+ static_cast<char>(roundManager->getRoundCount()
									+ 48) + "\n");

			//broadcast result of round
			broadcastRoundResult();

			roundManager->increaseRoundCount();

			std::cout << "\n";
			std::cout << "Team A score : " << roundManager->getScoreTeamA()
					<< std::endl;
			std::cout << "Team B score : " << roundManager->getScoreTeamB()
					<< std::endl;
			std::cout << "\n";
		}

		//checking if any team won the game
		if (roundManager->getScoreTeamA() == 7
				|| roundManager->getScoreTeamB() == 7) {
			std::cout << "\n";
			std::cout << "Team A score : " << roundManager->getScoreTeamA()
					<< std::endl;
			std::cout << "Team B score : " << roundManager->getScoreTeamB()
					<< std::endl;
			std::cout << "\n";
			std::cout << "Team "
					<< ((roundManager->getScoreTeamA()
							> roundManager->getScoreTeamB()) ? "A " : "B ")
					<< "has won the game" << std::endl;

			//broadcast the winner
			broadcastWinner();

			while (txBuffer->getMsgStatus())
				;			//loop till message is sent
			printer->printString("\n\nPress enter to exit...\n");
			std::cin.get();
			exit(0);
		}

		//decreasing no of total chances of game
		chanceCount--;

		//ask new player to play the move
		canPlayMove = true;
		break;
	}
	default: {
//			rxBuffer->setMsgStatus(false);
		//unknown message received
		printer->printString(
				"\nUnknown message received. Message will be ignored.\n");
		break;
	}
	}
	std::cout << "[MANAGE]: out of switch case. PlayerCount = " << playerCount
			<< std::endl;
	//command players to play move
	if (canPlayMove) {
		//first check which player is supposed to play
		roundManager->manageTurns(playerList);

		//play a move
		int i = 0;
		for (int i = 0; i < 4; i++) {
			if (playerList[i]->getIsPlaying()) {
				break;
			}
		}

		printer->printString("\nPlayer is now being asked to play the move\n");
		msgToPlayMove(playerList[i]->getPlayerID());

		//setting this variable to false to avoid random execution of this if-block
		canPlayMove = false;
	}

	//When all the players have joined the game, distribute them cards and ask for trump
	if (playerCount == 4) {
		//When all players have joined, print a message, send all players their info and distribute them cards
		printer->printString(
				"\n[MANAGE]:All players have joined. Game will now start. First 5 cards will be distributed\n");

		//broadcasting player info to update GUI of clients
		broadcastPlayerInfo(playerList);

		send5Cards(playerList[0]->getPlayerID(), playerList[0]->getCards());
		send5Cards(playerList[1]->getPlayerID(), playerList[1]->getCards());
		send5Cards(playerList[2]->getPlayerID(), playerList[2]->getCards());
		send5Cards(playerList[3]->getPlayerID(), playerList[3]->getCards());

		printer->printString(
				"\nAll players have received 5 cards. Now we will randomly ask for trump from the players\n");

		//sending message to randomly ask for trump
//		sendReqForTrump();

		//set player count to random value other than 4 so that program never enters into this if- execution
		playerCount++;
	}
	rxBuffer->setMsgStatus(false);
	std::cout << "[MANAGE]: Exiting client handle message function"
			<< std::endl;
}

/**
 * Function to broadcast the winner of game
 */
void GameManager::broadcastWinner(void) {
	char tempbuff[1] = {
			roundManager->getScoreTeamA() > roundManager->getScoreTeamB() ?
					static_cast<char>(static_cast<int>(TEAM::TEAMA) + 48) :
					static_cast<char>(static_cast<int>(TEAM::TEAMB) + 48) };

	while (txBuffer->getMsgStatus())
		;			//loop till message is available to write

	txBuffer->setWhichPlayer(ENTITY::BROADCAST);
	txBuffer->setFrameType(FRAMETYPE::BROADCASTWINNER);
	txBuffer->setDataType(DATATYPE::CHARACTER);
	txBuffer->setMsgLength(1);

	txBuffer->setMsgBuffer(tempbuff, 1);

	txBuffer->setMsgStatus(true);			// message is valid
}

/**
 * Function to broadcast the leaving of player which resulted into game over
 * @param id player ID denoting the player who left the game
 */
void GameManager::broadcastGameOver(char id) {
	char tempbuff[1] = { id };

	while (txBuffer->getMsgStatus())
		;			//loop till message is available to write

	txBuffer->setWhichPlayer(ENTITY::BROADCAST);
	txBuffer->setFrameType(FRAMETYPE::BROADCASTGAMEOVER);
	txBuffer->setDataType(DATATYPE::CHARACTER);
	txBuffer->setMsgLength(1);

	txBuffer->setMsgBuffer(tempbuff, 1);

	txBuffer->setMsgStatus(true);			// message is valid
}

/**
 * Function to broadcast the result after every round
 */
void GameManager::broadcastRoundResult(void) {
	char tempbuff[4] = { static_cast<char>(roundManager->getRoundCount() + 48),
			static_cast<char>(static_cast<int>(roundManager->getLastPlayerWon())
					+ 48),
			static_cast<char>(roundManager->getScoreTeamA() + 48),
			static_cast<char>(roundManager->getScoreTeamB() + 48) };

	while (txBuffer->getMsgStatus())
		;			//loop till message is available to write

	txBuffer->setWhichPlayer(ENTITY::PLAYER1);
	txBuffer->setFrameType(FRAMETYPE::BROADCASTRESULT);
	txBuffer->setDataType(DATATYPE::CHARACTER);
	txBuffer->setMsgLength(4);

	txBuffer->setMsgBuffer(tempbuff, 4);

	txBuffer->setMsgStatus(true);			// message is valid
}

/**
 * Function to broadcast information about different players , for e.g. name of players
 * @param playerList list of pointers pointing to objects of class Player
 */
void GameManager::broadcastPlayerInfo(Player** playerList) {
	char tempbuff[256];
	int k = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; playerList[i]->getPlayername()[j] != '\0'; j++) {
			tempbuff[k] = playerList[i]->getPlayername()[j];
			k++;
		}
		tempbuff[k] = '\0';
		k++;
	}
	std::cout << " waiting for tx buffer availability" << std::endl;
	while (txBuffer->getMsgStatus())
		;			//loop till message is available to write
	std::cout << " Tx buffer ready to be written" << std::endl;

	txBuffer->setWhichPlayer(ENTITY::BROADCAST);
	txBuffer->setFrameType(FRAMETYPE::BROADCASTPLAYERSINFO);
	txBuffer->setDataType(DATATYPE::CHARACTER);
	txBuffer->setMsgLength(k - 1);

	txBuffer->setMsgBuffer(tempbuff, k - 1);

	txBuffer->setMsgStatus(true);			// message is valid
}

/**
 * Function to broadcast the player moves
 * @param player It denotes which player's move is broadcasted
 * @param suit It denotes the suit of player's move
 * @param cardNumber It denotes the card number of player's move
 */
void GameManager::broadcastMove(int player, SUITS suit, int cardNumber) {
	while (txBuffer->getMsgStatus())
		;			//loop till message is available to write

	txBuffer->setWhichPlayer(ENTITY::BROADCAST);
	txBuffer->setFrameType(FRAMETYPE::BROADCASTMOVE);
	txBuffer->setDataType(DATATYPE::CHARACTER);
	txBuffer->setMsgLength(4);

	char tempbuff[4] = { static_cast<char>(player + 1 + 48),
			static_cast<char>(static_cast<int>(suit) + 48),
			static_cast<char>(cardNumber / 10 + 48),
			static_cast<char>(cardNumber % 10 + '0') };
	txBuffer->setMsgBuffer(tempbuff, 4);

	txBuffer->setMsgStatus(true);			// message is valid
}

/**
 * Function to send message to ask player to play a move
 */
void GameManager::msgToPlayMove(ENTITY player) {
	while (txBuffer->getMsgStatus())
		;			//loop till message is available to write

	txBuffer->setWhichPlayer(player);
	txBuffer->setFrameType(FRAMETYPE::TURNTOPLAY);
	txBuffer->setDataType(DATATYPE::CHARACTER);
	txBuffer->setMsgLength(0);
	txBuffer->flushBuffer();

	txBuffer->setMsgStatus(true);			// message is valid
}

/**
 * Function to send message to randomly ask for trump from players
 */
void GameManager::sendReqForTrump(void) {

	while (txBuffer->getMsgStatus())
		;			//loop till message is available to write

	txBuffer->setWhichPlayer(static_cast<ENTITY>((rand() % 4) + 1));
	txBuffer->setFrameType(FRAMETYPE::SETTRUMP);
	txBuffer->setDataType(DATATYPE::CHARACTER);
	txBuffer->setMsgLength(0);
	txBuffer->flushBuffer();

	txBuffer->setMsgStatus(true);			// message is valid

}

/**
 * Function to broadcast trump to all the players
 */
void GameManager::broadcastTrump(void) {
	while (txBuffer->getMsgStatus())
		;			//loop till message is available to write

	txBuffer->setWhichPlayer(ENTITY::BROADCAST);
	txBuffer->setFrameType(FRAMETYPE::BROADCASTTRUMP);
	txBuffer->setDataType(DATATYPE::CHARACTER);
	txBuffer->setMsgLength(1);

	char temp[1] = {
			static_cast<char>(static_cast<int>(roundManager->getTrump()) + 48) };

	txBuffer->setMsgBuffer(temp, 1);

	txBuffer->setMsgStatus(true);			// message is valid
}

/**
 * Function to broadcast to all the players that remaining cards are distributed
 */
void GameManager::sendRemainingCards(void) {
	while (txBuffer->getMsgStatus())
		;			//loop till message is available to write

	txBuffer->setWhichPlayer(ENTITY::BROADCAST);
	txBuffer->setFrameType(FRAMETYPE::REMAININGCARDS);
	txBuffer->setDataType(DATATYPE::CHARACTER);
	txBuffer->setMsgLength(0);
	txBuffer->flushBuffer();

	txBuffer->setMsgStatus(true);			// message is valid
}

/**
 * Function to send starting 5 cards to a player
 * @param who receiver of the message
 * @param cardarray pointer to the array of pointers which points to the objects of class Card
 */
void GameManager::send5Cards(ENTITY who, Card** cardarray) {
	char tempbuff[52];
	for (int i = 0; i < 13; ++i) {
		//set the suit in frame
		tempbuff[(i * 4)] = static_cast<int>(cardarray[i]->getSuit()) + '0';

		//set the card number in frame
		tempbuff[(i * 4) + 1] = (cardarray[i]->getCardNumber()) / 10 + '0';
		tempbuff[(i * 4) + 2] = (cardarray[i]->getCardNumber()) % 10 + '0';

		if (cardarray[i]->getCardValidity()) {
			tempbuff[(i * 4) + 3] = 'T';
		} else {
			tempbuff[(i * 4) + 3] = 'F';
		}
	}

	while (txBuffer->getMsgStatus())
		;			//loop till message is available to write

	txBuffer->setWhichPlayer(who);
	txBuffer->setFrameType(FRAMETYPE::FIRST5CARDS);
	txBuffer->setDataType(DATATYPE::CHARACTER);
	txBuffer->setMsgLength(52);
	txBuffer->setMsgBuffer(tempbuff, 52);

	txBuffer->setMsgStatus(true);			// message is valid
}

/**
 * Function to send acknowledgement message with ID and team name
 * @param who receiver of the message
 * @param team team of the player
 */
void GameManager::sendAckMessage(ENTITY who, TEAM team) {
	printer->printString(
			"\n[MANAGE]: Sending acknowledgement message to player for joining the game\n");
	printer->printString(
			"\n[MANAGE]: Waiting for Tx buffer to be free to edit\n");
	while (txBuffer->getMsgStatus())
		;			//loop till message is available to write
	printer->printString("\n[MANAGE]: Tx buffer ready to be modified\n");
	char tempbuff[2] = { static_cast<char>(static_cast<int>(who) + 48),
			static_cast<char>(static_cast<int>(team) + 48) };

	txBuffer->setWhichPlayer(who);
	txBuffer->setFrameType(FRAMETYPE::ACKJOINREQ);
	txBuffer->setDataType(DATATYPE::CHARACTER);
	txBuffer->setMsgLength(2);
	txBuffer->setMsgBuffer(tempbuff, 2);

	txBuffer->setMsgStatus(true);			// message is valid
	std::cout << "[MANAGE]: Exiting send ACK function" << std::endl;

}

/**
 * Destructor for class Game Manager
 */
GameManager::~GameManager() {
	std::cout << "Destructor for class Game Manager called" << std::endl;
	isThreadAlive = false;
	SDL_WaitThread(network_thread, NULL);
}
