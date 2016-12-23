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

#ifndef TICTACTOEBOARD_H
#define TICTACTOEBOARD_H

/* Number of board rows: the board is a square */
const unsigned int BOARD_NO_OF_ROWS = 3;

/* Length of winning line */
const int BOARD_LENGTH_OF_WINNING_LINE = 3;

/* State of the cell: empty, X or O */
enum BOARD_CELL_STATE {EMPTY = 0, 
	                   O = 1, 
					   X = 2
                      };

/* Value for AI in the next move */
enum BOARD_MOVE_SCORE {SCORE_EMPTY_FIELD = 1,
	                   SCORE_CENTER_FIELD = 1,
					   SCORE_CHANCE_IN_FUTURE = 2,
					   SCORE_FOIL_ENEMY_MOVE = 10,
					   SCORE_PREVENT_FROM_DEFEAT = 100,
					   SCORE_WIN_IN_NEXT_MOVE = 1000
                      };

/* results of player move */
const int MOVE_SUCCESS = 0;
const int MOVE_ERROR_FIELD_OCCUPIED = 1;
const int MOVE_ERROR_X_INCORRECT = 2;
const int MOVE_ERROR_Y_INCORRECT = 3;

/* TicTacToe Board */
class TicTacToeBoard : public Board
{
public:
	/* Constructors */
	TicTacToeBoard (void);
	virtual TicTacToeBoard* Clone (void);

	/* Destructors */
	virtual ~TicTacToeBoard (void);

	/* Basic board management */
	int MarkMove (USHORT x, USHORT y, BOARD_CELL_STATE mark);
	BOARD_CELL_STATE GetMark (USHORT x, USHORT y) const;
	BOARD_CELL_STATE GetWinner (void) const;
	BOARD_CELL_STATE GetOpponent (BOARD_CELL_STATE mark) const;
	bool IsFull (void) const;
	bool IsWinPossible (void) const;
	UINT GetNumberOfWiningPlaces (BOARD_CELL_STATE mark);

	/* Graphics */
	void Draw (void) const;

private:
	/* Extended board management */
	void Init (void);

	/* Board data structures */
	BOARD_CELL_STATE board[BOARD_NO_OF_ROWS][BOARD_NO_OF_ROWS];	
};

#endif /* TICTACTOEBOARD_H */