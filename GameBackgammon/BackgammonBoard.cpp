#include "stdafx.h"
#include "BackgammonBoard.h"

/*
Constructor
Inits a starting board
*/
BackgammonBoard::BackgammonBoard (void)
{
	int i;

	/* all fields empty */
	for (i= 0; i < NUMBER_OF_FIELDS; i++)
	{
		this->board[i][PLAYER_HUMAN]= 0;
		this->board[i][PLAYER_MACHINE]= 0;
	}

	/* some of them should have something */
	this->board[0][PLAYER_HUMAN]= 2;
	this->board[5][PLAYER_MACHINE]= 5;
	this->board[7][PLAYER_MACHINE]= 3;
	this->board[11][PLAYER_HUMAN]= 5;
	this->board[12][PLAYER_MACHINE]= 5;
	this->board[16][PLAYER_HUMAN]= 3;
	this->board[18][PLAYER_HUMAN]= 5;
	this->board[23][PLAYER_MACHINE]= 2;
	this->board[18][PLAYER_HUMAN]= 5;
	this->board[23][PLAYER_MACHINE]= 2;

	/* home and finish - they are empty */
	/* tokens cannot be removed yet */
	for (i= 0; i < NUMBER_OF_COLORS; i++)
	{
		this->home[i]= 0;	
		this->finish[i]= 0;
		this->tokensAtFinalQuarter[i]= false;
	}

	this->tokensSeparated= false;
}

/*
Destructor
Does nothing so far
*/
BackgammonBoard::~BackgammonBoard (void)
{

}

/*
Returns number of players' tokens left in base
*/
UINT
BackgammonBoard::GetTokensAtHome (USHORT colorNo) const
{
	return home[colorNo];
}

/*
Returns number of players' tokens already taken out the board
*/
UINT
BackgammonBoard::GetTokensAtFinish (USHORT colorNo) const
{
	return finish[colorNo];
}

/*
Returns number of players' tokens left on board, including these left in the base
*/
UINT
BackgammonBoard::GetTokensLeft (USHORT colorNo) const
{
	int i;
	UINT sum= 0;

	for (i= 0; i < NUMBER_OF_FIELDS; i++)
	{
		sum+= this->board[i][colorNo];
	}

	sum+= GetTokensAtHome (colorNo);

	return sum;
}

/* Calculates score for a given board and player
   The lower score, the better */
UINT
BackgammonBoard::CalculateScore (USHORT colorNo, bool withAI) const
{
	USHORT score = 0;
	int i;

	/* human */
	if (colorNo == PLAYER_HUMAN)
	{
		for (i= 0; i < NUMBER_OF_FIELDS; i++)
		{
			if (this->board[i][colorNo] > 0)
			{
				/* points per each token left */
				score+= (this->board[i][colorNo])*SCORE_HUMAN[i];
			}

			if (withAI)
			{
				/* points per single token left */
				if (this->board[i][colorNo] == 1)
				{
					/* TODO: check if there are any opponent's tokens before that can hit it */
					score+= SCORE_SINGLE_TOKEN;
				}
			}
		}

		if (this->board[BOARD_HOME_VALUE][colorNo] > 0)
		{
			score+= this->board[BOARD_HOME_VALUE][colorNo]*SCORE_HUMAN[BOARD_HOME_VALUE];
		}
	}
	/* machine */
	else
	{
		for (i= 0; i < NUMBER_OF_FIELDS; i++)
		{
			if (this->board[i][colorNo] > 0)
			{
				/* points per each token left */
				score+= (this->board[i][colorNo])*SCORE_MACHINE[i];
			}

			if (withAI)
			{
				/* points per single token left */
				if (this->board[i][colorNo] == 1)
				{
					/* TO DO: check if there are any opponent's tokens before that can hit it */
					score+= SCORE_SINGLE_TOKEN;
				}
			}
		}

		if (this->board[BOARD_HOME_VALUE][colorNo] > 0)
		{
			score+= this->board[BOARD_HOME_VALUE][colorNo]*SCORE_MACHINE[BOARD_HOME_VALUE];
		}
	}
	
	return score;
}

/* Checks if tokens are separated - players cannot hit opponent's tokens during their moves */
bool
BackgammonBoard::CheckIfTokensAreSeparated (void) const
{
	bool isHumanTokenFound = false;
	int i;

	/* if there are still some tokens at start - tokens are not separated for sure */
	if ( (this->home[PLAYER_HUMAN] > 0) || (this->home[PLAYER_MACHINE] > 0 ) )
	{
		return false;
	}

	/* if all tokens are outside home field */
	for (i= 0; i < NUMBER_OF_FIELDS; i++)
	{
		/* remember that at least one human token is found */
		if ( this->board[i][PLAYER_HUMAN] > 0)
		{
			isHumanTokenFound= true;
		}
		/* we already found human token and now there is a machine token */
		/* if tokens are separated, there are no human tokens before machine tokens */
		if ( (isHumanTokenFound ) && ( this->board[i][PLAYER_MACHINE] > 0) )
		{
			return false;
		}
	}

	/* tokens are separated */
	return true;
}

/*
Sets token separation
*/
void 
BackgammonBoard::SetTokensSeparation (bool separated)
{
	this->tokensSeparated = separated;
}

/*
Gets token separation
*/
bool
BackgammonBoard::GetTokensSeparation (void) const
{
	return (this->tokensSeparated);
}

/*
Sets marker of tokens at final quarter
*/
void 
BackgammonBoard::SetTokensAtFinalQuarter (bool marker, USHORT playerNo)
{
	this->tokensAtFinalQuarter[playerNo] = marker;
}

/*
Gets marker of tokens at final quarter
*/
bool
BackgammonBoard::GetTokensAtFinalQuarter (USHORT playerNo) const
{
	return (this->tokensAtFinalQuarter[playerNo]);
}

/*
Check if all tokens left are in the final quarter
*/
bool
BackgammonBoard::CheckIfAllTokensInFinishQuarter (USHORT colorNo) const
{
	int i;
	UINT sum= 0;

	/* human goes forward */
	if (colorNo == PLAYER_HUMAN)
	{
		for (i= 0; i < NUMBER_OF_FIELDS- 6; i++)
		{
			sum+= this->board[i][PLAYER_HUMAN];
		}
		if ((sum == 0) && (GetTokensAtHome(PLAYER_HUMAN) == 0))
		{
			return true;
		}
	}
	/* machine goes backward */
	else if (colorNo == PLAYER_MACHINE)
	{
		for (i= NUMBER_OF_FIELDS- 1; i > 5; i--)
		{
			sum+= this->board[i][PLAYER_MACHINE];
		}
		if ((sum == 0) && (GetTokensAtHome(PLAYER_MACHINE) == 0))
		{
			return true;
		}
	}
	return false;
}

/*
Marks move on board
- Returns 0 on success
- Otherwise an error
*/
int
BackgammonBoard::MarkMove (USHORT oldPosition, USHORT newPosition, USHORT colorNo)
{
	USHORT opponentColor;

	if (oldPosition == newPosition)
	{
		/* no move */
		return MOVE_ERROR_NO_MOVE;
	}
	else if ((GetTokensAtHome(colorNo) > 0) && (oldPosition != BOARD_HOME_VALUE))
	{
		/* trying to move on board if some tokens are still at home */
		return MOVE_ERROR_TOKENS_LEFT_AT_HOME;
	}
	else if (this->board[oldPosition][colorNo] == 0)
	{
		/* no token available at source */
		return MOVE_ERROR_NO_TOKENS_AVAILABLE;
	}
	else
	{
		if (newPosition >= NUMBER_OF_FIELDS)
		{
			/* TO DO */
			/* Check if there is a move possible without moving outside board */

			if (!CheckIfAllTokensInFinishQuarter(colorNo))
			{
				/* token cannot go to finish yet */
				return MOVE_ERROR_CANNOT_FINISH_YET;
			}
			else
			{
				/* token goes to finish */
				this->board[oldPosition][colorNo]--;
				this->finish[colorNo]++;
			}
		}
		else
		{
			opponentColor= GetOpponentColor (colorNo);
			if (this->board[newPosition][opponentColor] > NUMBER_OF_TOKENS_TO_HIT)
			{
				/* cannot move because there are opponents' token left on the destination field */
				return MOVE_ERROR_FIELD_ALREADY_OCCUPIED;
			}
			else
			{
				/* token moves on board */
				this->board[oldPosition][colorNo]--;
				this->board[newPosition][colorNo]++;

				/* hit opponent's token and move it to the base */
				if (this->board[newPosition][opponentColor] == NUMBER_OF_TOKENS_TO_HIT)
				{
					this->board[newPosition][opponentColor]= 0;
					this->home[opponentColor]+= NUMBER_OF_TOKENS_TO_HIT;
				}
			}
		}
	}

	return MOVE_SUCCESS;
}

/*
Returns color of the opponent
*/
USHORT
BackgammonBoard::GetOpponentColor (USHORT colorNo)
{
	if (colorNo == PLAYER_HUMAN)
	{
		return PLAYER_MACHINE;
	}
	return PLAYER_HUMAN;
}

/*
Cloning the board
*/
BackgammonBoard* 
BackgammonBoard::Clone (void)
{
	BackgammonBoard* boardCopy;
	int i;

	boardCopy = new BackgammonBoard ();

	/* copy all fields */
	for (i= 0; i < NUMBER_OF_FIELDS; i++)
	{		
		boardCopy->board[i][PLAYER_HUMAN] = this->board[i][PLAYER_HUMAN];
		boardCopy->board[i][PLAYER_MACHINE] = this->board[i][PLAYER_MACHINE];
	}
	/* including home and finish */
	for (i= 0; i < NUMBER_OF_COLORS; i++)
	{
		boardCopy->home[i]= this->home[i];
		boardCopy->finish[i]= this->finish[i];
	}

	return (boardCopy);
}

/*
Draws a board
*/
void
BackgammonBoard::Draw(BackgammonPlayer* currentPlayer) const
{
	int i;
	HANDLE  hConsole;

	hConsole= GetStdHandle(STD_OUTPUT_HANDLE);  
	SetConsoleTextAttribute(hConsole, WHITE);

	/* line above */
	std::cout << "  +";
	for (i= 0; i < 5; i++)
	{
		std::cout << "-";
	}
	std::cout << "+";
	for (i= 0; i < 5; i++)
	{
		std::cout << "-";
	}
	std::cout << "+" << std::endl;

	/* lines */
	for (i= 0; i < NUMBER_OF_FIELDS/4; i++)
	{
		std::cout << " " << LETTER[i];
		std::cout << "|";
		if (this->board[i][PLAYER_HUMAN] > 0)
		{
			FlushConsoleInputBuffer(hConsole);     
			SetConsoleTextAttribute(hConsole, YELLOW); 
		}
		else if (this->board[i][PLAYER_MACHINE] > 0)
		{
			FlushConsoleInputBuffer(hConsole);     
			SetConsoleTextAttribute(hConsole, RED); 
		}
		if ((this->board[i][PLAYER_HUMAN] > 5) || (this->board[i][PLAYER_MACHINE] > 5))
		{       	
			std::cout << "oooo+";
		}
		else if ((this->board[i][PLAYER_HUMAN] == 5) || (this->board[i][PLAYER_MACHINE] == 5))
		{
			std::cout << "ooooo";
		}
		else if ((this->board[i][PLAYER_HUMAN] == 4) || (this->board[i][PLAYER_MACHINE] == 4))
		{
			std::cout << "oooo ";
		}
		else if ((this->board[i][PLAYER_HUMAN] == 3) || (this->board[i][PLAYER_MACHINE] == 3))
		{
			std::cout << "ooo  ";
		}
		else if ((this->board[i][PLAYER_HUMAN] == 2) || (this->board[i][PLAYER_MACHINE] == 2))
		{
			std::cout << "oo   ";
		}
		else if ((this->board[i][PLAYER_HUMAN] == 1) || (this->board[i][PLAYER_MACHINE] == 1))
		{
			std::cout << "o    ";
		}
		else if ((this->board[i][PLAYER_HUMAN] == 0) && (this->board[i][PLAYER_MACHINE] == 0))
		{
			std::cout << "     ";
		}

		SetConsoleTextAttribute(hConsole, WHITE);
		std::cout << "|";

		if (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] > 0)
		{
			FlushConsoleInputBuffer(hConsole);     
			SetConsoleTextAttribute(hConsole, YELLOW); 
		}
		else if (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] > 0)
		{
			FlushConsoleInputBuffer(hConsole);     
			SetConsoleTextAttribute(hConsole, RED); 
		}
		if ((this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] > 5) || (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] > 5))
		{       	
			std::cout << "oooo+";
		}
		else if ((this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] == 5) || (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] == 5))
		{
			std::cout << "ooooo";
		}
		else if ((this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] == 4) || (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] == 4))
		{
			std::cout << "oooo ";
		}
		else if ((this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] == 3) || (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] == 3))
		{
			std::cout << "ooo  ";
		}
		else if ((this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] == 2) || (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] == 2))
		{
			std::cout << "oo   ";
		}
		else if ((this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] == 1) || (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] == 1))
		{
			std::cout << "o    ";
		}
		else if ((this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] == 0) || (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] == 0))
		{
			std::cout << "     ";
		}
		SetConsoleTextAttribute(hConsole, WHITE);				
		std::cout << "|";
		std::cout << LETTER[NUMBER_OF_FIELDS- i- 1];

		if (i == 0)
		{			
			std::cout << "   " << LETTER[BOARD_HOME_VALUE] << " Tokens at home:   ";
			FlushConsoleInputBuffer(hConsole);     
			SetConsoleTextAttribute(hConsole, YELLOW);
			std::cout << this->home[PLAYER_HUMAN] << "  ";
			FlushConsoleInputBuffer(hConsole);     
			SetConsoleTextAttribute(hConsole, RED);
			std::cout << this->home[PLAYER_MACHINE];
		}
		else if (i == 1)
		{
			std::cout << "   " << LETTER[BOARD_FINISH_VALUE] << " Tokens at finish: ";
			FlushConsoleInputBuffer(hConsole);     
			SetConsoleTextAttribute(hConsole, YELLOW);
			std::cout << this->finish[PLAYER_HUMAN] << "  ";
			FlushConsoleInputBuffer(hConsole);     
			SetConsoleTextAttribute(hConsole, RED);
			std::cout << this->finish[PLAYER_MACHINE];
		}
		else if (i == 3)
		{
			std::cout << "     Your dice left: ";			
			if (currentPlayer->GetDice(DICE_ONE) > 0)
			{
				std::cout << currentPlayer->GetDice(DICE_ONE) << " ";
			}
			if (currentPlayer->GetDice(DICE_TWO) > 0)
			{
				std::cout << currentPlayer->GetDice(DICE_TWO) << " ";
			}
			if (currentPlayer->GetDice(DICE_ONE_DOUBLE) > 0)
			{
				std::cout << currentPlayer->GetDice(DICE_ONE_DOUBLE) << " ";
			}
			if (currentPlayer->GetDice(DICE_TWO_DOUBLE) > 0)
			{
				std::cout << currentPlayer->GetDice(DICE_TWO_DOUBLE) << " ";
			}
		}
		else if (i == 5)
		{
			std::cout << "     Tokens are separated?        ";
			if (this->tokensSeparated)
			{
				SetConsoleTextAttribute(hConsole, YELLOW);
				std::cout << "yes";
			}
			else
			{
				SetConsoleTextAttribute(hConsole, RED);
				std::cout << "no";
			}
		}

		FlushConsoleInputBuffer(hConsole);     
		SetConsoleTextAttribute(hConsole, WHITE);

		std::cout << std::endl;
	}

	/* line in the middle */
	std::cout << "  +";
	for (i= 0; i < 5; i++)
	{
		std::cout << "-";
	}
	std::cout << "+";
	for (i= 0; i < 5; i++)
	{
		std::cout << "-";
	}
	std::cout << "+";
	
	std::cout << "      All tokens at final quarter? ";
	SetConsoleTextAttribute(hConsole, YELLOW);
	if (this->tokensAtFinalQuarter[PLAYER_HUMAN])
	{		
		std::cout << "yes";
	}
	else
	{	
		std::cout << "no";
	}
	std::cout << " ";
	SetConsoleTextAttribute(hConsole, RED);
	if (this->tokensAtFinalQuarter[PLAYER_MACHINE])
	{		
		std::cout << "yes";
	}
	else
	{	
		std::cout << "no";
	}
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << std::endl;

	/* lines */
	for (i= NUMBER_OF_FIELDS/4; i < NUMBER_OF_FIELDS/2; i++)
	{
		std::cout << " " << LETTER[i];
		std::cout << "|";
		if (this->board[i][PLAYER_HUMAN] > 0)
		{
			FlushConsoleInputBuffer(hConsole);     
			SetConsoleTextAttribute(hConsole, YELLOW); 
		}
		else if (this->board[i][PLAYER_MACHINE] > 0)
		{
			FlushConsoleInputBuffer(hConsole);     
			SetConsoleTextAttribute(hConsole, RED); 
		}
		if ((this->board[i][PLAYER_HUMAN] > 5) || (this->board[i][PLAYER_MACHINE] > 5))
		{       	
			std::cout << "oooo+";
		}
		else if ((this->board[i][PLAYER_HUMAN] == 5) || (this->board[i][PLAYER_MACHINE] == 5))
		{
			std::cout << "ooooo";
		}
		else if ((this->board[i][PLAYER_HUMAN] == 4) || (this->board[i][PLAYER_MACHINE] == 4))
		{
			std::cout << "oooo ";
		}
		else if ((this->board[i][PLAYER_HUMAN] == 3) || (this->board[i][PLAYER_MACHINE] == 3))
		{
			std::cout << "ooo  ";
		}
		else if ((this->board[i][PLAYER_HUMAN] == 2) || (this->board[i][PLAYER_MACHINE] == 2))
		{
			std::cout << "oo   ";
		}
		else if ((this->board[i][PLAYER_HUMAN] == 1) || (this->board[i][PLAYER_MACHINE] == 1))
		{
			std::cout << "o    ";
		}
		else if ((this->board[i][PLAYER_HUMAN] == 0) && (this->board[i][PLAYER_MACHINE] == 0))
		{
			std::cout << "     ";
		}

		SetConsoleTextAttribute(hConsole, WHITE);
		std::cout << "|";

		if (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] > 0)
		{
			FlushConsoleInputBuffer(hConsole);     
			SetConsoleTextAttribute(hConsole, YELLOW); 
		}
		else if (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] > 0)
		{
			FlushConsoleInputBuffer(hConsole);     
			SetConsoleTextAttribute(hConsole, RED); 
		}
		if ((this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] > 5) || (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] > 5))
		{       	
			std::cout << "oooo+";
		}
		else if ((this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] == 5) || (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] == 5))
		{
			std::cout << "ooooo";
		}
		else if ((this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] == 4) || (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] == 4))
		{
			std::cout << "oooo ";
		}
		else if ((this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] == 3) || (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] == 3))
		{
			std::cout << "ooo  ";
		}
		else if ((this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] == 2) || (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] == 2))
		{
			std::cout << "oo   ";
		}
		else if ((this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] == 1) || (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] == 1))
		{
			std::cout << "o    ";
		}
		else if ((this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_HUMAN] == 0) || (this->board[NUMBER_OF_FIELDS- i- 1][PLAYER_MACHINE] == 0))
		{
			std::cout << "     ";
		}
		SetConsoleTextAttribute(hConsole, WHITE);				
		std::cout << "|";
		std::cout << LETTER[NUMBER_OF_FIELDS- i- 1];

		if (i == NUMBER_OF_FIELDS/4+ 1)
		{			
			std::cout << "     Score:   ";
			FlushConsoleInputBuffer(hConsole);     
			SetConsoleTextAttribute(hConsole, YELLOW);
			std::cout << this->CalculateScore (PLAYER_HUMAN, false) << "  ";
			FlushConsoleInputBuffer(hConsole);     
			SetConsoleTextAttribute(hConsole, RED);
			std::cout << this->CalculateScore (PLAYER_MACHINE, false);
		}

		FlushConsoleInputBuffer(hConsole);     
		SetConsoleTextAttribute(hConsole, WHITE);

		std::cout << std::endl;
	}

	/* line below */
	std::cout << "  +";
	for (i= 0; i < 5; i++)
	{
		std::cout << "-";
	}
	std::cout << "+";
	for (i= 0; i < 5; i++)
	{
		std::cout << "-";
	}
	std::cout << "+" << std::endl;
}

