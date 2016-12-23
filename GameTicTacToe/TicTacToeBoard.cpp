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

#include "stdafx.h"
#include "TicTacToeBoard.h"
#include "TicTacToePlayer.h"

/*
Constructor
Inits an empty board
*/
TicTacToeBoard::TicTacToeBoard (void)
{
	int i, j;

	/* inits main board - all fields are empty */
	for (i= 0; i < BOARD_NO_OF_ROWS; i++)
	{
		for (j= 0; j < BOARD_NO_OF_ROWS; j++)
		{
			this->board[i][j]= EMPTY;
		}		
	}
}

/*
Destructor
Does nothing so far
*/
TicTacToeBoard::~TicTacToeBoard (void)
{

}

/*
Marks move on board
- Returns 0 on success
- Returns 1 on trying to set non-empty field
- Returns -1 if x is out-of-board
- Returns -2 if y is out-of-board
*/
int 
TicTacToeBoard::MarkMove (USHORT x, USHORT y, BOARD_CELL_STATE mark)
{
	/* check boundaries */
	if ((x < 0) || ( x >= BOARD_NO_OF_ROWS))
	{
		return MOVE_ERROR_X_INCORRECT;
	}
	if ((y < 0) || ( y >= BOARD_NO_OF_ROWS))
	{
		return MOVE_ERROR_Y_INCORRECT;
	}

	/* mark a sign on board if not marked yet*/
	if (this->board[x][y] == EMPTY)
	{
		this->board[x][y]= mark;
		return MOVE_SUCCESS;
	}
	else
	{
		return MOVE_ERROR_FIELD_OCCUPIED;
	}
}

/* 
Finds a winner of game
*/
BOARD_CELL_STATE
TicTacToeBoard::GetWinner (void) const
{
	const USHORT winningO= 1;
	const USHORT winningX= 8;
	int i, j, result;
	bool isAnyEmpty= false;

	/* 
	if result == 0 - no line
	if result == 1 - line of O - O is the winner
	if result == 2^n (n>0) - line of X - X is the winner
	*/

	/* discover horizontal lines */
	for (i= 0; i < BOARD_NO_OF_ROWS; i++)
	{
		result= 1;
		for (j= 0; j < BOARD_NO_OF_ROWS; j++)
		{
			result*= this->board[i][j];
		}
		if ((result == winningX) || (result == winningO))
		{
			/* the first mark in the line indicates the winner */
			return (this->board[i][0]);			
		}
	}

	/* discover vertical lines */
	for (j= 0; j < BOARD_NO_OF_ROWS; j++)
	{
		result= 1;
		for (i= 0; i < BOARD_NO_OF_ROWS; i++)
		{
			result*= this->board[i][j];
		}
		if ((result == winningX) || (result == winningO))
		{
			/* the first mark in the line indicates the winner */
			return (this->board[0][j]);			
		}
	}

	/* discover cross lines */
	result= 1;
	for (i= 0; i < BOARD_NO_OF_ROWS; i++)
	{
		result*= this->board[i][i];
	}
	if ((result == winningX) || (result == winningO))
	{
		/* the first mark in the line indicates the winner */
		return (this->board[0][0]);
	}
	result= 1;
	for (i= BOARD_NO_OF_ROWS- 1, j= 0; i >= 0, j < BOARD_NO_OF_ROWS; i--, j++)
	{
		result*= this->board[i][j];
	}
	if ((result == winningX) || (result == winningO))
	{
		/* the first mark in the line indicates the winner */
		return (this->board[0][BOARD_NO_OF_ROWS - 1]);
	}

	/* no winner yet */
	return (EMPTY);
}

/* 
Checks if board is full
*/
bool
TicTacToeBoard::IsFull (void) const
{
	int i, j;
	for (i= 0; i < BOARD_NO_OF_ROWS; i++)
	{
		for (j= 0; j < BOARD_NO_OF_ROWS; j++)
		{
			/* check for any empty field left */
			if (this->board[i][j] == EMPTY)
			{
				return false;
			}
		}
	}
	/* all fields are not empty */
	return true;	
}

/* 
Checks if one player win is still possible
*/
bool
TicTacToeBoard::IsWinPossible (void) const
{
	int i, j;
	/* 8 possible winning lines: 3 horizontal, 3 vertical, 2 diagonal */
	unsigned short int result= 8;
	unsigned short int sumPlayer1, sumPlayer2;

	/* discover horizontal line impossibility */
	for (i= 0; i < BOARD_NO_OF_ROWS; i++)
	{
		sumPlayer1= 0;
		sumPlayer2= 0;
		for (j= 0; j < BOARD_NO_OF_ROWS; j++)
		{
			if (this->board[i][j] == O)
			{
				sumPlayer1++;
			}
			if (this->board[i][j] == X)
			{
				sumPlayer2++;
			}
		}
		if ((sumPlayer1 > 0) && (sumPlayer2 > 0))
		{
			result--;
		}
	}

	/* discover vertical line impossibility */
	for (j= 0; j < BOARD_NO_OF_ROWS; j++)
	{
		sumPlayer1= 0;
		sumPlayer2= 0;
		for (i= 0; i < BOARD_NO_OF_ROWS; i++)
		{
			if (this->board[i][j] == O)
			{
				sumPlayer1++;
			}
			if (this->board[i][j] == X)
			{
				sumPlayer2++;
			}
		}
		if ((sumPlayer1 > 0) && (sumPlayer2 > 0))
		{
			result--;
		}
	}

	/* discover up-left, down-right cross line danger */
	sumPlayer1= 0;
	sumPlayer2= 0;
	for (i= 0, j= 0; i < BOARD_NO_OF_ROWS, j < BOARD_NO_OF_ROWS; i++, j++)
	{
		if (this->board[i][j] == O)
		{
			sumPlayer1++;
		}
		if (this->board[i][j] == X)
		{
			sumPlayer2++;
		}
	}
	if ((sumPlayer1 > 0) && (sumPlayer2 > 0))
	{
		result--;
	}

	/* discover down-left, up-right cross line danger */
	sumPlayer1= 0;
	sumPlayer2= 0;
	for (i= BOARD_NO_OF_ROWS- 1, j= 0; i >= 0, j < BOARD_NO_OF_ROWS; i--, j++)
	{
		if (this->board[i][j] == O)
		{
			sumPlayer1++;
		}
		if (this->board[i][j] == X)
		{
			sumPlayer2++;
		}
	}
	if ((sumPlayer1 > 0) && (sumPlayer2 > 0))
	{
		result--;
	}

	/* check if any of possible winning lines is still possible to be drawn */
	if (result > 0)
	{
		/* still win is possible */
		return true;
	}
	else
	{
		/* no win possible */
		return false;
	}
}

/*
Assume that you have one move and you can put it
Check in how many places you can put your mark and win
*/
UINT
TicTacToeBoard::GetNumberOfWiningPlaces (BOARD_CELL_STATE mark)
{
	int i, j;
	UINT number= 0;
	TicTacToeBoard* futureBoard;

	for (i= 0; i < BOARD_NO_OF_ROWS; i++)
	{
		for (j= 0; j < BOARD_NO_OF_ROWS; j++)
		{
			if (this->GetMark(i, j) == EMPTY)
			{
				futureBoard= this->Clone ();
				futureBoard->MarkMove (i, j, mark);		
				if (futureBoard->GetWinner() == mark)
				{	
					number++;
				}
				free (futureBoard);
				futureBoard = 0;
			}
		}
	}
	return number;
}

/*
Gets mark put in the given board coordinates
*/
BOARD_CELL_STATE
TicTacToeBoard::GetMark (USHORT x, USHORT y) const
{
	return (this->board[x][y]);
}

/*
Draws a board
*/
void
TicTacToeBoard::Draw(void) const
{
	int i, j, k;
	HANDLE  hConsole;

	hConsole= GetStdHandle(STD_OUTPUT_HANDLE);  

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

			switch (this->board[i][j])
			{
			case EMPTY:
				std::cout << " ";
				break;
			case X:
				FlushConsoleInputBuffer(hConsole);     
				SetConsoleTextAttribute(hConsole, RED);              	
				std::cout << "x";
				SetConsoleTextAttribute(hConsole, WHITE);
				break;
			case O:
				FlushConsoleInputBuffer(hConsole);     
				SetConsoleTextAttribute(hConsole, YELLOW);   
				std::cout << "o";
				SetConsoleTextAttribute(hConsole, WHITE);
				break;
			}
			std::cout << " | ";
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

/*
Cloning the board
*/
TicTacToeBoard* 
TicTacToeBoard::Clone (void)
{
	TicTacToeBoard* boardCopy;
	int i, j;

	boardCopy = new TicTacToeBoard ();

	for (i= 0; i < BOARD_NO_OF_ROWS; i++)
	{
		for (j= 0; j < BOARD_NO_OF_ROWS; j++)
		{
			boardCopy->board[i][j] = this->board[i][j];
		}
	}

	return (boardCopy);
}

/*
Returns opponent for the given player
*/
BOARD_CELL_STATE
TicTacToeBoard::GetOpponent (BOARD_CELL_STATE player) const
{
	if (player == X)
	{
		return O;
	}
	else if (player == O)
	{
		return X;
	}
	else
	{
		return EMPTY;
	}
}