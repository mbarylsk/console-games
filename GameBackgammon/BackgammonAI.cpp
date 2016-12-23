#include "stdafx.h"
#include "BackgammonBoard.h"
#include "BackgammonAI.h"

/*
Constructor
Inits AI score board
*/
BackgammonAI::BackgammonAI (void)
{

}

/*
Destructor
Does nothing so far
*/
BackgammonAI::~BackgammonAI (void)
{

}

/*
Calculates AI score for a given field on board
*/
int
BackgammonAI::CalculateScore (BackgammonBoard* board, USHORT colorNo) const
{
	int score = 0;

	score= board->CalculateScore (colorNo, true);
	
	return score;
}

/*
Calculates the best move for AI for the whole board
*/
int
BackgammonAI::FindBestMove (BackgammonBoard* board, USHORT &oldPosition, USHORT &newPosition, BackgammonPlayer* player)
{
	USHORT start, end;
	USHORT diceSum;
	int x;
	UINT score= SCORE_MACHINE[24]*SCORE_MACHINE[24];
	UINT currentScore= 0;
	BackgammonBoard* futureBoard;

	/* find all possible moves */
	for (diceSum= 1; diceSum <= 24; diceSum++)
	{
		if (player->CheckIfDiceCombinationIsAvailable (diceSum, true))
		{
			if (player->IsMachine())
			{
				for (x= NUMBER_OF_FIELDS; x >= 0; x--)
				{
					if (x- diceSum >= 0)
					{
						futureBoard= board->Clone ();
				
						if (futureBoard->MarkMove (x, x- diceSum, player->GetNumber()) == MOVE_SUCCESS)
						{
							currentScore = CalculateScore(futureBoard, player->GetNumber());
							if (currentScore < score)
							{
								score= currentScore;
								start= x;
								end= x- diceSum;
							}
						}

						free (futureBoard);
						futureBoard = NULL;
					}
				}
			}
		}
	}

	/* set the best results */
	oldPosition = start;
	newPosition = end;
	
	/* return the best score */
	return score;
}

/*
Draws an AI plans for the next move
*/
void
BackgammonAI::Draw(void) const
{
	
}