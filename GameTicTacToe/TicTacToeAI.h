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
#include "TicTacToeBoard.h"
#include "TicTacToeAI.h"
#include "AI.h"

#ifndef TICTACTOEAI_H
#define TICTACTOEAI_H

/* TicTacToe Player */
class TicTacToeAI : public AI
{
public:
	/* Constructors */
	TicTacToeAI (void);

	/* Destructors */
	virtual ~TicTacToeAI (void);

	/* Score calculation */
	int FindBestMove (TicTacToeBoard* board, USHORT &px, USHORT &py, BOARD_CELL_STATE mark);

	/* Graphics */
	void Draw (void) const;

private:
	/* Score calculation */
	int CalculateScore (TicTacToeBoard* board, USHORT x, USHORT y, BOARD_CELL_STATE mark) const;
	int boardAIScore[BOARD_NO_OF_ROWS][BOARD_NO_OF_ROWS];
};

#endif /* TICTACTOEAI_H */