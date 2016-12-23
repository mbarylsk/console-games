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
#include "AI.h"
#include "BackgammonBoard.h"
#include "BackgammonAI.h"

#ifndef BACKGAMMONAI_H
#define BACKGAMMONAI_H

/* Backgammon AI */
class BackgammonAI : public AI
{
public:
	/* Constructors */
	BackgammonAI (void);

	/* Destructors */
	virtual ~BackgammonAI (void);

	/* Score calculation */
	int FindBestMove (BackgammonBoard* board, USHORT &oldPosition, USHORT &newPosition, BackgammonPlayer* player);

	/* Graphics */
	void Draw (void) const;

private:
	/* Score calculation */
	int CalculateScore (BackgammonBoard* board, USHORT colorNo) const;
	int boardAIScore[NUMBER_OF_FIELDS][NUMBER_OF_COLORS];
};

#endif /* BACKGAMMONAI_H */