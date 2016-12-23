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