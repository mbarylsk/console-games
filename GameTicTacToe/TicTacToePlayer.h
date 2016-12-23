#pragma once
#include "stdafx.h"
#include "Player.h"
#include "TicTacToeBoard.h"
#include <windows.h>

#ifndef TICTACTOEPLAYER_H
#define TICTACTOEPLAYER_H

/* TicTacToe Player */
class TicTacToePlayer : public Player
{
public:
	/* Constructors */
	TicTacToePlayer (void);
	TicTacToePlayer (BOARD_CELL_STATE mark, bool machine, int color, bool active);

	/* Destructors */
	virtual ~TicTacToePlayer (void);

	/* Management */
	BOARD_CELL_STATE GetMark (void) const;

	/* Graphics */
	void PrintName (void) const;
	void PrintMark (void) const;

private:
	/* Player mark */
	BOARD_CELL_STATE mark;
};

#endif /* TICTACTOEPLAYER_H */