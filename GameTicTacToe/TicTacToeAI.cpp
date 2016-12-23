#include "stdafx.h"
#include "TicTacToeBoard.h"
#include "TicTacToeAI.h"

/*
Constructor
Inits AI score board
*/
TicTacToeAI::TicTacToeAI (void)
{
	int i, j;

	/* inits AI scores for board fields - 1 for all fields */
	for (i= 0; i < BOARD_NO_OF_ROWS; i++)
	{
		for (j= 0; j < BOARD_NO_OF_ROWS; j++)
		{
			this->boardAIScore[i][j]= 1;
		}		
	}
}

/*
Destructor
Does nothing so far
*/
TicTacToeAI::~TicTacToeAI (void)
{

}

/*
Calculates AI score for a given field on board
*/
int
TicTacToeAI::CalculateScore (TicTacToeBoard* board, USHORT x, USHORT y, BOARD_CELL_STATE player) const
{
	int i, j, finalResult= 0;
	UINT sumEnemyOptions= 0, sumEnemy= 0, sumFriend= 0, sumEmpty= 0;
	TicTacToeAI futureAI;
	TicTacToeBoard* futureBoard;
	USHORT futureX, futureY;

	if (board->GetMark(x, y) != EMPTY)
	{
		/* non-empty field should not be used - set the lowest possible value */
		return finalResult;
	}
	else
	{
		/* increase AI value by 1 point because field is empty */
		finalResult+= SCORE_EMPTY_FIELD;

		/* if in the middle of board - add 1 extra point */
		if ((x > 0) && (x < BOARD_NO_OF_ROWS- 1) && (y > 0) && (y < BOARD_NO_OF_ROWS- 1))
		{
			finalResult+= SCORE_CENTER_FIELD;
		}

		/* discover vertical line danger */
		sumEnemy= 0;
		sumFriend= 0;
		sumEmpty= 0;
		for (i= x- BOARD_LENGTH_OF_WINNING_LINE+ 1; i <= x+ BOARD_LENGTH_OF_WINNING_LINE- 1; i++)
		{
			if ((i >= 0) && (i < BOARD_NO_OF_ROWS))
			{

				if ((board->GetMark(i, y) != EMPTY) && (board->GetMark(i, y) != player))
				{
					sumEnemy++;
				}
				if ((board->GetMark(i, y) != EMPTY) && (board->GetMark(i, y) == player))
				{
					sumFriend++;
				}
				if (board->GetMark(i, y) == EMPTY)
				{
					sumEmpty++;
				}
			}
		}
		/* win with this move */
		if (sumFriend == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= SCORE_WIN_IN_NEXT_MOVE;
		}
		/* prevent from defeat */
		if (sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= SCORE_PREVENT_FROM_DEFEAT;
		}
		/* foil enemy good move */
		if ((sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 2) && (sumFriend == 0))
		{
			sumEnemyOptions++;
		}
		/* your chance to win in the future */
		if (sumFriend + sumEmpty == BOARD_LENGTH_OF_WINNING_LINE)
		{
			finalResult+= SCORE_CHANCE_IN_FUTURE;
		}

		/* discover horizontal line danger */
		sumEnemy= 0;
		sumFriend= 0;
		sumEmpty= 0;
		for (i= y- BOARD_LENGTH_OF_WINNING_LINE+ 1; i <= y+ BOARD_LENGTH_OF_WINNING_LINE- 1; i++)
		{
			if ((i >= 0) && (i < BOARD_NO_OF_ROWS))
			{
				if ((board->GetMark(x, i) != EMPTY) && (board->GetMark(x, i) != player))
				{
					sumEnemy++;
				}
				if ((board->GetMark(x, i) != EMPTY) && (board->GetMark(x, i) == player))
				{
					sumFriend++;
				}
				if (board->GetMark(x, i) == EMPTY)
				{
					sumEmpty++;
				}
			}
		}
		/* win with this move */
		if (sumFriend == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= SCORE_WIN_IN_NEXT_MOVE;
		}
		/* prevent from defeat */
		if (sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= SCORE_PREVENT_FROM_DEFEAT;
		}
		/* foil enemy good move */
		if ((sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 2) && (sumFriend == 0))
		{
			sumEnemyOptions++;
		}
		/* your chance to win in the future */
		if (sumFriend + sumEmpty == BOARD_LENGTH_OF_WINNING_LINE)
		{
			finalResult+= SCORE_CHANCE_IN_FUTURE;
		}

		/* discover up-left, down-right cross line danger */
		sumEnemy= 0;
		sumFriend= 0;
		sumEmpty= 0;
		for (i= x- BOARD_LENGTH_OF_WINNING_LINE+ 1, j= y- BOARD_LENGTH_OF_WINNING_LINE+ 1; i <= x+ BOARD_LENGTH_OF_WINNING_LINE- 1, j <= y+ BOARD_LENGTH_OF_WINNING_LINE- 1; i++, j++)
		{
			if ((i >= 0) && (i < BOARD_NO_OF_ROWS) && (j >= 0) && (j < BOARD_NO_OF_ROWS))
			{
				if ((board->GetMark(i, j) != EMPTY) && (board->GetMark(i, j) != player))
				{
					sumEnemy++;
				}
				if ((board->GetMark(i, j) != EMPTY) && (board->GetMark(i, j) == player))
				{
					sumFriend++;
				}
				if (board->GetMark(i, j) == EMPTY)
				{
					sumEmpty++;
				}
			}
		}
		/* win with this move */
		if (sumFriend == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= SCORE_WIN_IN_NEXT_MOVE;
		}
		/* prevent from defeat */
		if (sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= SCORE_PREVENT_FROM_DEFEAT;
		}
		/* foil enemy good move */
		if ((sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 2) && (sumFriend == 0))
		{
			sumEnemyOptions++;
		}
		/* your chance to win in the future */
		if (sumFriend + sumEmpty == BOARD_LENGTH_OF_WINNING_LINE)
		{
			finalResult+= SCORE_CHANCE_IN_FUTURE;
		}

		/* discover down-left, up-right cross line danger */
		sumEnemy= 0;
		sumFriend= 0;
		sumEmpty= 0;
		for (i= x+ BOARD_LENGTH_OF_WINNING_LINE- 1, j= y- BOARD_LENGTH_OF_WINNING_LINE+ 1; i >= 0, j <= y+ BOARD_LENGTH_OF_WINNING_LINE- 1; i--, j++)
		{
			if ((i >= 0) && (i < BOARD_NO_OF_ROWS) && (j >= 0) && (j < BOARD_NO_OF_ROWS))
			{
				if ((board->GetMark(i, j) != EMPTY) && (board->GetMark(i, j) != player))
				{
					sumEnemy++;
				}
				if ((board->GetMark(i, j) != EMPTY) && (board->GetMark(i, j) == player))
				{
					sumFriend++;
				}
				if (board->GetMark(i, j) == EMPTY)
				{
					sumEmpty++;
				}
			}
		}
		/* win with this move */
		if (sumFriend == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= SCORE_WIN_IN_NEXT_MOVE;
		}
		/* prevent from defeat */
		if (sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= SCORE_PREVENT_FROM_DEFEAT;
		}
		/* foil enemy good move */
		if ((sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 2) && (sumFriend == 0))
		{
			sumEnemyOptions++;
		}
		/* your chance to win in the future */
		if (sumFriend + sumEmpty == BOARD_LENGTH_OF_WINNING_LINE)
		{
			finalResult+= SCORE_CHANCE_IN_FUTURE;
		}

		/* finally, foil enemy good move */
		if (sumEnemyOptions > 1)
		{
			finalResult+= SCORE_FOIL_ENEMY_MOVE;
		}

		/* if current move is not the very best move (neither win nor prevention from defeat) */	
		if (finalResult < SCORE_PREVENT_FROM_DEFEAT)
		{
			futureBoard = board->Clone ();
				
			futureBoard->MarkMove (x, y, player);

			futureAI.FindBestMove (futureBoard, futureX, futureY, board->GetOpponent (player));
			futureBoard->MarkMove (futureX, futureY, board->GetOpponent (player));

			if (futureBoard->GetNumberOfWiningPlaces(board->GetOpponent (player)) > 1)
			{
				finalResult= 1;				
			}
			
			free (futureBoard);
		}
	
		return finalResult;
	}
}

/*
Calculates the best move for AI for the whole board
*/
int
TicTacToeAI::FindBestMove (TicTacToeBoard* board, USHORT &px, USHORT &py, BOARD_CELL_STATE mark)
{
	int i, j, score= 0, futureScore= 0;
	USHORT x, y;

	/* calculate all AI scores */
	for (i= 0; i < BOARD_NO_OF_ROWS; i++)
	{
		for (j= 0; j < BOARD_NO_OF_ROWS; j++)
		{
			this->boardAIScore[i][j]= CalculateScore (board, i, j, mark);
		}
	}

	/* go through all fields and find cell coordinates with the highest AI score */
	for (i= 0; i < BOARD_NO_OF_ROWS; i++)
	{
		for (j= 0; j < BOARD_NO_OF_ROWS; j++)
		{
			if (this->boardAIScore[i][j] > score)
			{
				x= i;
				y= j;
				score= this->boardAIScore[i][j];
			}
		}
	}
		
	/* set the best coordinates */
	px= x;
	py= y;

	/* return the highest score */
	return score;
}

/*
Draws an AI plans for the next move
*/
void
TicTacToeAI::Draw(void) const
{
	int i, j, k;

	std::cout << "     ";
	for (j= 0; j < BOARD_NO_OF_ROWS; j++)
	{
		std::cout << j << "   ";
	}
	std::cout << "y" << std::endl;
	std::cout << "   +";
	for (k= 0; k < BOARD_NO_OF_ROWS; k++)
	{
		std::cout << "---+";
	}
	std::cout << std::endl;
	for (i= 0; i < BOARD_NO_OF_ROWS; i++)
	{
		std::cout << " " << i << " | ";
		for (j= 0; j < BOARD_NO_OF_ROWS; j++)
		{
			std::cout << boardAIScore[i][j] << " | ";
		}		
		std::cout << std::endl;
		std::cout << "   +";
		for (k= 0; k < BOARD_NO_OF_ROWS; k++)
		{
			std::cout << "---+";
		}
		std::cout << std::endl;		
	}
	std::cout << " x" << std::endl;
}