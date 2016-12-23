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
#include <stdlib.h>
#include <time.h>
#include <limits>
#include "Player.h"

#ifndef BACKGAMMONPLAYER_H
#define BACKGAMMONPLAYER_H

const short int NUMBER_OF_DICE_NORMAL = 2;
const short int NUMBER_OF_DICE = NUMBER_OF_DICE_NORMAL*2;

/* standard dice */
const short int DICE_NUMBER = 4;
const short int DICE_ONE = 0;
const short int DICE_TWO = 1;
/* these two dice are filled only if there is a duplicate on the first two */
const short int DICE_ONE_DOUBLE = 2;
const short int DICE_TWO_DOUBLE = 3;
const USHORT PLAYER_HUMAN = 0;
const USHORT PLAYER_MACHINE = 1;

/* Backgammon Player */
class BackgammonPlayer : public Player
{
public:
	/* Constructors */
	BackgammonPlayer (void);
	BackgammonPlayer (bool machine, int color, bool active);

	/* Destructors */
	virtual ~BackgammonPlayer (void);

	/* Dice management */
	USHORT GetDice (int diceNo) const;
	void ThrowDice (void);
	bool CheckIfDiceCombinationIsAvailable (USHORT diceSum, bool insideBoard);	
	void UseDice (USHORT diceSum);

	/* Player management */
	USHORT GetNumber (void) const;

	/* Graphics */
	void PrintName (void) const;

private:
	/* Extended dice management */
	void ZeroDice (int diceNo);

	/* Player data */
	USHORT dice[NUMBER_OF_DICE];
};

#endif /* BACKGAMMONPLAYER_H */