#include "stdafx.h"
#include "BackgammonPlayer.h"

/*
Constructor
*/
BackgammonPlayer::BackgammonPlayer (bool machine, int color, bool active):
Player (machine, color, active)
{

}

/*
Destructor
*/
BackgammonPlayer::~BackgammonPlayer(void)
{

}

/*
Gets die value; 0 if dice number is incorrect
*/
USHORT
BackgammonPlayer::GetDice (int diceNo) const
{
	if ((diceNo < 0) || (diceNo >= NUMBER_OF_DICE))
	{
		return 0;
	}
	return (this->dice[diceNo]);
}

/*
Zeros die
*/
void
BackgammonPlayer::ZeroDice (int diceNo)
{
	this->dice[diceNo] = 0;
}

/*
Throws both dice for a given player
*/
void
BackgammonPlayer::ThrowDice (void)
{
	int i;

	/* initialize random seed: */
	srand ( (unsigned int)time(NULL) );

	/* throw dice, one-by-one */
	for (i= 0; i < NUMBER_OF_DICE_NORMAL; i++)
	{
		/* lottery: allowed values: 1, 2, 3, 4, 5, 6 */
		this->dice[i]= 1+ rand () % 6;
	}

	/* if duplicate, moves are doubled */
	if (this->dice[DICE_ONE] == this->dice[DICE_TWO])
	{
		this->dice[DICE_ONE_DOUBLE] = this->dice[DICE_ONE];
		this->dice[DICE_TWO_DOUBLE] = this->dice[DICE_TWO];
	}
	else
	{
		this->dice[DICE_ONE_DOUBLE]= 0;
		this->dice[DICE_TWO_DOUBLE]= 0;
	}
}

/*
Checks if a given combination of dice is available
*/
bool
BackgammonPlayer::CheckIfDiceCombinationIsAvailable (USHORT diceSum, bool insideBoard)
{
	/* no sum */
	if (diceSum == 0)
	{
		return false;
	}
	/* single dice within board */
	if (insideBoard)
	{
		if ( (this->dice[DICE_ONE] == diceSum) || (this->dice[DICE_TWO] == diceSum) || (this->dice[DICE_ONE_DOUBLE] == diceSum) || (this->dice[DICE_TWO_DOUBLE] == diceSum))
		{
			return true;
		}
	}
	/* single dice outside board */
	else
	{
		if ( (this->dice[DICE_ONE] >= diceSum) || (this->dice[DICE_TWO] >= diceSum) || (this->dice[DICE_ONE_DOUBLE] >= diceSum) || (this->dice[DICE_TWO_DOUBLE] >= diceSum))
		{
			return true;
		}
	}

	/* otherwise no dice available */
	return false;
}

/*
Marks dice as used
*/
void
BackgammonPlayer::UseDice (USHORT diceSum)
{
	/* if dice sum is incorrect - do nothing */
	if (diceSum == 0)
	{
		return;
	}

	/* if dice is exact */
	/* 1 dice - 4 combinations */
	if (GetDice(DICE_ONE) == diceSum)
	{
		ZeroDice(DICE_ONE);
		return;
	}
	else if (GetDice(DICE_TWO) == diceSum)
	{
		ZeroDice(DICE_TWO);
		return;
	}
	else if (GetDice(DICE_ONE_DOUBLE) == diceSum)
	{
		ZeroDice(DICE_ONE_DOUBLE);
		return;
	}
	else if (GetDice(DICE_TWO_DOUBLE) == diceSum)
	{
		ZeroDice(DICE_TWO_DOUBLE);
		return;
	}
	/* if diceSum is a combination of dice */
	/* 2 dice - 6 combinations */
	else if (GetDice(DICE_ONE) + GetDice(DICE_TWO) == diceSum)
	{
		ZeroDice(DICE_ONE);
		ZeroDice(DICE_TWO);
		return;
	}
	else if (GetDice(DICE_ONE) + GetDice(DICE_ONE_DOUBLE) == diceSum)
	{
		ZeroDice(DICE_ONE);
		ZeroDice(DICE_ONE_DOUBLE);
		return;
	}
	else if (GetDice(DICE_TWO) + GetDice(DICE_TWO_DOUBLE) == diceSum)
	{
		ZeroDice(DICE_TWO);
		ZeroDice(DICE_TWO_DOUBLE);
		return;
	}
	else if (GetDice(DICE_ONE) + GetDice(DICE_TWO_DOUBLE) == diceSum)
	{
		ZeroDice(DICE_ONE);
		ZeroDice(DICE_TWO_DOUBLE);
		return;
	}
	else if (GetDice(DICE_TWO) + GetDice(DICE_ONE_DOUBLE) == diceSum)
	{
		ZeroDice(DICE_TWO);
		ZeroDice(DICE_ONE_DOUBLE);
		return;
	}
	else if (GetDice(DICE_ONE_DOUBLE) + GetDice(DICE_TWO_DOUBLE) == diceSum)
	{		
		ZeroDice(DICE_ONE_DOUBLE);
		ZeroDice(DICE_TWO_DOUBLE);
		return;
	}
	/* 3 dice - 4 combinations */
	else if (GetDice(DICE_ONE) + GetDice(DICE_ONE_DOUBLE) + GetDice(DICE_TWO_DOUBLE) == diceSum)
	{
		ZeroDice(DICE_ONE);
		ZeroDice(DICE_ONE_DOUBLE);
		ZeroDice(DICE_TWO_DOUBLE);
		return;
	}
	else if (GetDice(DICE_TWO) + GetDice(DICE_ONE_DOUBLE) + GetDice(DICE_TWO_DOUBLE) == diceSum)
	{
		ZeroDice(DICE_TWO);
		ZeroDice(DICE_ONE_DOUBLE);
		ZeroDice(DICE_TWO_DOUBLE);
		return;
	}
	else if (GetDice(DICE_ONE) + GetDice(DICE_TWO) + GetDice(DICE_ONE_DOUBLE) == diceSum)
	{
		ZeroDice(DICE_ONE);
		ZeroDice(DICE_TWO);
		ZeroDice(DICE_ONE_DOUBLE);
		ZeroDice(DICE_TWO_DOUBLE);
		return;
	}
	else if (GetDice(DICE_ONE) + GetDice(DICE_TWO) + GetDice(DICE_TWO_DOUBLE) == diceSum)
	{
		ZeroDice(DICE_ONE);
		ZeroDice(DICE_TWO);
		ZeroDice(DICE_ONE_DOUBLE);
		ZeroDice(DICE_TWO_DOUBLE);
		return;
	}
	/* 4 dice - 1 combination */
	else if (GetDice(DICE_ONE) + GetDice(DICE_TWO) + GetDice(DICE_ONE_DOUBLE) + GetDice(DICE_TWO_DOUBLE) == diceSum)
	{
		ZeroDice(DICE_ONE);
		ZeroDice(DICE_TWO);
		ZeroDice(DICE_ONE_DOUBLE);
		ZeroDice(DICE_TWO_DOUBLE);
		return;
	}
}

/*
Prints information about player: either human or computer
*/
void
BackgammonPlayer::PrintName (void) const
{
	HANDLE hConsole;
					
	hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);

	SetConsoleTextAttribute(hConsole, this->GetColor());
	if (this->IsMachine())
	{
		std::cout << "Computer ";
	}
	else
	{
		std::cout << "You ";
	}

	/* sets color back to white */
	SetConsoleTextAttribute(hConsole, WHITE);
}

/*
Gets player number
*/
USHORT
BackgammonPlayer::GetNumber (void) const
{
	if (this->IsMachine ())
	{
		return PLAYER_MACHINE;
	}
	else
	{
		return PLAYER_HUMAN;
	}
}