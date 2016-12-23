#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>

#ifndef GAME_H
#define GAME_H

/* Generic game */
class Game
{
public:
	/* Constructor */
	Game(void);

	/* Destructor */
	virtual ~Game(void);

	/* State of the game */
	virtual bool IsCompleted (void) = 0;

	/* Version of the game */
	std::string GetVersion (void) const;
	void SetVersion (std::string);

	/* Moves counter */
	void IncreaseMovesCount (void);
	int GetMovesCount (void) const;

protected:
	/* version of the game */
	std::string version;
	/* number of moves */
	int numberOfMoves;
};

#endif /* GAME_H */