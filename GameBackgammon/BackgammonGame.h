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
#include "Game.h"
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <ctype.h>
#include <string>
#include "BackgammonBoard.h"
#include "BackgammonPlayer.h"
#include "BackgammonAI.h"

#ifndef BACKGAMMONGAME_H
#define BACKGAMMONGAME_H

const std::string GAME_VERSION = "1.0.0.33";
const short int NUMBER_OF_PLAYERS = 2;
const int GAME_SCREEN_WIDTH = 79;

/* Backgammon game */
class BackgammonGame : public Game
{
public:
	/* Constructors */
	BackgammonGame (bool isLoterry);

	/* Destructors */
	virtual ~BackgammonGame (void);

	/* Game management */
	void RefreshProperties (void);
	bool IsCompleted (void);
	int Move (USHORT oldPosistion, USHORT newPosition, BackgammonPlayer* player);
	void AICoordinates (BackgammonAI* ai, USHORT &oldPosistion, USHORT &newPosition, BackgammonPlayer* player);

	/* Input */
	void ReadCoordinates (USHORT &oldPosistion, USHORT &newPosition, BackgammonPlayer* player) const;

	/* Graphics */
	void Draw (BackgammonPlayer* currentPlayer) const;
	void PrintRules (void) const;
	void PrintBanner (void) const;
	void PrintStartScreen (void) const;
	void PrintHorizontalLine (void) const;
	void PrintError (int error) const;

	/* Player management */
	BackgammonPlayer* GetWinner (void) const;
	BackgammonPlayer* GetCurrentPlayer (void) const;
	bool ArePlayerMovesDone (BackgammonPlayer* player);
	UINT GetNumberOfPossibleMoves (BackgammonPlayer* player);
	void SetNextPlayer (void);

private:
	/* Advanced game management */
	USHORT TranslateLetterToCoordinate (std::string letter) const;
	char TranslateCoordinateToLetter (USHORT value) const;

	/* Game board */
	BackgammonBoard board;

	/* Player data structures */	
	BackgammonPlayer* winner;	
	BackgammonPlayer* players[NUMBER_OF_PLAYERS];
};

#endif /* BACKGAMMONGAME_H */