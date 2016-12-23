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