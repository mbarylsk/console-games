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