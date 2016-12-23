/*
Copyright(C) 2012-2016  Marcin Barylski

This program is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include "stdafx.h"
#include <windows.h>
#include "Board.h"
#include "BackgammonPlayer.h"

#ifndef BACKGAMMONBOARD_H
#define BACKGAMMONBOARD_H

/* Board construction */
const USHORT NUMBER_OF_FIELDS = 24;
const USHORT NUMBER_OF_COLORS = 2;
const USHORT BOARD_HOME_VALUE = 24;    /* special coordinate for home */
const USHORT BOARD_FINISH_VALUE = 25;  /* special coordinate for finish */
const USHORT NUMBER_OF_LETTERS = 26;
/* board from 0 to 23; home at 24, finish at 25 */
const char LETTER[NUMBER_OF_LETTERS]= 
           {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
            'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
			'U', 'V', 'W', 'X', 'Y', 'Z'};

/* Value for AI in the next move */
enum BOARD_SCORE {SCORE_TOKEN = 1,
	              SCORE_SINGLE_TOKEN = 10					   
                 };

/* board from 0 to 23; home at 24, finish at 25 */
const USHORT SCORE_HUMAN[NUMBER_OF_LETTERS]=
             {24, 23, 22, 21, 20, 19, 18, 17, 16, 15,
			  14, 13, 12, 11, 10, 9,  8,  7,  6,  5,
			  4,  3,  2,  1, 25, 0};

/* board from 0 to 23; home at 24, finish at 25 */
const USHORT SCORE_MACHINE[NUMBER_OF_LETTERS]=
             {1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
			  11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
			  21, 22, 23, 24, 25, 0};

/* errors */
const USHORT ERROR_WRONG_LETTER = 255;
const int MOVE_SUCCESS = 0;
const int MOVE_ERROR_NO_SUCH_DICE_AVAILABLE = 50;
const int MOVE_ERROR_INCORRECT_DIRECTION = 51;
const int MOVE_ERROR_NO_MOVE = 52;
const int MOVE_ERROR_TOKENS_LEFT_AT_HOME = 53;
const int MOVE_ERROR_NO_TOKENS_AVAILABLE = 54;
const int MOVE_ERROR_FIELD_ALREADY_OCCUPIED = 55;
const int MOVE_ERROR_CANNOT_FINISH_YET = 56;
const int MOVE_ERROR_USE_HOME_FIRST = 57;
const int MOVE_ERROR_PLAYER_BLOCKED = 58;

/* other constants */
const int NUMBER_OF_TOKENS_TO_HIT = 1;

/* Backgammon Board */
class BackgammonBoard : public Board
{
public:
	/* Constructors */
	BackgammonBoard (void);
	virtual BackgammonBoard* Clone (void);

	/* Destructors */
	virtual ~BackgammonBoard (void);

	/* Board basic management */	
	int MarkMove (USHORT oldPosition, USHORT newPosition, USHORT colorNo);
	UINT CalculateScore (USHORT colorNo, bool withAI) const;

	/* Tokens management */
	UINT GetTokensLeft (USHORT colorNo) const;
	UINT GetTokensAtHome (USHORT colorNo) const;
	UINT GetTokensAtFinish (USHORT colorNo) const;
	bool CheckIfAllTokensInFinishQuarter (USHORT colorNo) const;	
	bool CheckIfTokensAreSeparated (void) const;
	void SetTokensSeparation (bool separated);
	bool GetTokensSeparation (void) const;	
	void SetTokensAtFinalQuarter (bool marker, USHORT colorNo);
	bool GetTokensAtFinalQuarter (USHORT colorNo) const;	
	
	/* Graphics */
	void Draw (BackgammonPlayer* currentPlayer) const;

private:
	/* Extended board management */
	USHORT GetOpponentColor(USHORT colorNo);
	
	/* Board data structures */
	UINT board[NUMBER_OF_FIELDS][NUMBER_OF_COLORS];
	UINT home[NUMBER_OF_COLORS];
	UINT finish[NUMBER_OF_COLORS];
	bool tokensSeparated;
	bool tokensAtFinalQuarter[NUMBER_OF_COLORS];
};

#endif /* BACKGAMMONBOARD_H */