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