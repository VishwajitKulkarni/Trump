/*
 * misc.h
 *
 *  Created on: Dec 6, 2017
 *      Author: vishwajit
 */

#ifndef INCLUDE_SERVERMISC_H_
#define INCLUDE_SERVERMISC_H_

#include <stdlib.h>

#define BUFFERSIZE 50
#define FRAME_SOF 0x07E
#define FRAME_EOF 0x07F
#define MESSAGE_AVAILABLE true
#define MESSAGE_NOT_AVAILABLE false
typedef enum playerID {
	_Server = 0,
	_PLAYER1 = 1,
	_PLAYER2 = 2,
	_PLAYER3 = 3,
	_PLAYER4 = 4,
	_INVALIDPLAYER = -1
} _PlayerNumber;
//
#endif /* INCLUDE_SERVERMISC_H_ */
