#pragma once
#include "stdafx.h"
#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <windows.h>
#include "TicTacToeBoard.h"
#include "TicTacToePlayer.h"
#include "TicTacToeAI.h"

#ifndef TICTACTOEGAME_H
#define TICTACTOEGAME_H

const std::string GAME_VERSION = "1.0.0.37";
const short int NUMBER_OF_PLAYERS = 2;

/* TicTacToe game */
class TicTacToeGame : public Game
{
public:
	/* Constructors */
	TicTacToeGame (bool isLottery);

	/* Destructors */
	virtual ~TicTacToeGame (void);

	/* Game management */	
	int Move (USHORT x, USHORT y, TicTacToePlayer* player);
	bool IsCompleted (void);
	void AICoordinates (TicTacToeAI* ai, USHORT& rx, USHORT& ry, TicTacToePlayer* player);
	void PressEnterToContinue (void) const;

	/* Input */
	void ReadCoordinates (USHORT& rx, USHORT& ry, TicTacToePlayer* player) const;

	/* Graphics */
	void Draw (void) const;
	void PrintBanner (void) const;
	void PrintRules (void) const;
	void PrintStartScreen (void) const;
	void PrintEndScreen (void) const;
	
	/* Player management */
	TicTacToePlayer* GetWinner (void) const;
	TicTacToePlayer* GetCurrentPlayer (void) const;	
	TicTacToePlayer* GetPlayerWithMark (BOARD_CELL_STATE mark) const;
	void SetNextPlayer (void);

private:
	/* Game board data structures */
	TicTacToeBoard board;

	/* Player data structures */	
	TicTacToePlayer* winner;	
	TicTacToePlayer* players[NUMBER_OF_PLAYERS];
};

#endif /* TICTACTOEGAME_H */