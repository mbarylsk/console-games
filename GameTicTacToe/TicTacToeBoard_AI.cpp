#include "stdafx.h"
#include "TicTacToeBoard.h"
#include "TicTacToePlayer.h"

/*
Calculates AI score for a given field on board
*/
int TicTacToeBoard::AICalculateScore (USHORT x, USHORT y, BOARD_CELL_STATE player) const
{
	int i, j, finalResult= 0;
	UINT sumEnemyOptions= 0, sumEnemy= 0, sumFriend= 0, sumEmpty= 0;
	TicTacToeBoard boardTest;

	if (this->board[x][y] != EMPTY)
	{
		/* non-empty field should not be used - set the lowest possible value */
		return finalResult;
	}
	else
	{
		/* increase AI value by 1 point because field is empty */
		finalResult+= 1;

		/* if in the middle of board - add 1 extra point */
		if ((x > 0) && (x < BOARD_NO_OF_ROWS- 1) && (y > 0) && (y < BOARD_NO_OF_ROWS- 1))
		{
			finalResult+= 1;
		}

		/* discover vertical line danger */
		sumEnemy= 0;
		sumFriend= 0;
		sumEmpty= 0;
		for (i= x- BOARD_LENGTH_OF_WINNING_LINE+ 1; i <= x+ BOARD_LENGTH_OF_WINNING_LINE- 1; i++)
		{
			if ((i >= 0) && (i < BOARD_NO_OF_ROWS))
			{

				if ((this->board[i][y] != EMPTY) && (this->board[i][y] != player))
				{
					sumEnemy++;
				}
				if ((this->board[i][y] != EMPTY) && (this->board[i][y] == player))
				{
					sumFriend++;
				}
				if (this->board[i][y] == EMPTY)
				{
					sumEmpty++;
				}
			}
		}
		/* win with this move */
		if (sumFriend == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= 1000;
		}
		/* prevent from defeat */
		if (sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= 100;
		}
		/* foil enemy good move */
		if ((sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 2) && (sumFriend == 0))
		{
			sumEnemyOptions++;
		}
		/* your chance to win in the future */
		if (sumFriend + sumEmpty == BOARD_LENGTH_OF_WINNING_LINE)
		{
			finalResult+= 2;
		}

		/* discover horizontal line danger */
		sumEnemy= 0;
		sumFriend= 0;
		sumEmpty= 0;
		for (i= y- BOARD_LENGTH_OF_WINNING_LINE+ 1; i <= y+ BOARD_LENGTH_OF_WINNING_LINE- 1; i++)
		{
			if ((i >= 0) && (i < BOARD_NO_OF_ROWS))
			{
				if ((this->board[x][i] != EMPTY) && (this->board[x][i] != player))
				{
					sumEnemy++;
				}
				if ((this->board[x][i] != EMPTY) && (this->board[x][i] == player))
				{
					sumFriend++;
				}
				if (this->board[x][i] == EMPTY)
				{
					sumEmpty++;
				}
			}
		}
		/* win with this move */
		if (sumFriend == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= 1000;
		}
		/* prevent from defeat */
		if (sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= 100;
		}
		/* foil enemy good move */
		if ((sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 2) && (sumFriend == 0))
		{
			sumEnemyOptions++;
		}
		/* your chance to win in the future */
		if (sumFriend + sumEmpty == BOARD_LENGTH_OF_WINNING_LINE)
		{
			finalResult+= 2;
		}

		/* discover up-left, down-right cross line danger */
		sumEnemy= 0;
		sumFriend= 0;
		sumEmpty= 0;
		for (i= x- BOARD_LENGTH_OF_WINNING_LINE+ 1, j= y- BOARD_LENGTH_OF_WINNING_LINE+ 1; i <= x+ BOARD_LENGTH_OF_WINNING_LINE- 1, j <= y+ BOARD_LENGTH_OF_WINNING_LINE- 1; i++, j++)
		{
			if ((i >= 0) && (i < BOARD_NO_OF_ROWS) && (j >= 0) && (j < BOARD_NO_OF_ROWS))
			{
				if ((this->board[i][j] != EMPTY) && (this->board[i][j] != player))
				{
					sumEnemy++;
				}
				if ((this->board[i][j] != EMPTY) && (this->board[i][j] == player))
				{
					sumFriend++;
				}
				if (this->board[i][j] == EMPTY)
				{
					sumEmpty++;
				}
			}
		}
		/* win with this move */
		if (sumFriend == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= 1000;
		}
		/* prevent from defeat */
		if (sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= 100;
		}
		/* foil enemy good move */
		if ((sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 2) && (sumFriend == 0))
		{
			sumEnemyOptions++;
		}
		/* your chance to win in the future */
		if (sumFriend + sumEmpty == BOARD_LENGTH_OF_WINNING_LINE)
		{
			finalResult+= 2;
		}

		/* discover down-left, up-right cross line danger */
		sumEnemy= 0;
		sumFriend= 0;
		sumEmpty= 0;
		for (i= x+ BOARD_LENGTH_OF_WINNING_LINE- 1, j= y- BOARD_LENGTH_OF_WINNING_LINE+ 1; i >= 0, j <= y+ BOARD_LENGTH_OF_WINNING_LINE- 1; i--, j++)
		{
			if ((i >= 0) && (i < BOARD_NO_OF_ROWS) && (j >= 0) && (j < BOARD_NO_OF_ROWS))
			{
				if ((this->board[i][j] != EMPTY) && (this->board[i][j] != player))
				{
					sumEnemy++;
				}
				if ((this->board[i][j] != EMPTY) && (this->board[i][j] == player))
				{
					sumFriend++;
				}
				if (this->board[i][j] == EMPTY)
				{
					sumEmpty++;
				}
			}
		}
		/* win with this move */
		if (sumFriend == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= 1000;
		}
		/* prevent from defeat */
		if (sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 1)
		{
			finalResult+= 100;
		}
		/* foil enemy good move */
		if ((sumEnemy == BOARD_LENGTH_OF_WINNING_LINE- 2) && (sumFriend == 0))
		{
			sumEnemyOptions++;
		}
		/* your chance to win in the future */
		if (sumFriend + sumEmpty == BOARD_LENGTH_OF_WINNING_LINE)
		{
			finalResult+= 2;
		}

		/* finally, foil enemy good move */
		if (sumEnemyOptions > 1)
		{
			finalResult+= 10;
		}

		//if (board.GetNumberOfWiningPlaces()


		return finalResult;
	}
}

/*
Calculates the best move for AI for the whole board
*/
void TicTacToeBoard::AIFindBestMove (USHORT &px, USHORT &py, BOARD_CELL_STATE mark)
{
	int i, j, score= 0;
	USHORT x, y;

	/* calculate all AI scores */
	for (i= 0; i < BOARD_NO_OF_ROWS; i++)
	{
		for (j= 0; j < BOARD_NO_OF_ROWS; j++)
		{
			this->boardAIScore[i][j]= AICalculateScore (i, j, mark);
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
}
