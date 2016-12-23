#pragma once
#include "stdafx.h"

#ifndef PLAYER_H
#define PLAYER_H

/* Player of the game */
class Player
{
public:
	/* Constructor */
	Player (bool machine, int color, bool active);

	/* Destructor */
	virtual ~Player(void);

	/* Player properties */
	bool IsMachine (void) const;
	bool IsActive (void) const;
	int GetColor (void) const;
	void MakeActive (void);
	void MakeInactive (void);

protected:
	/* Player properties */
	bool machine;
	bool active;
	int color;
};

#endif /* PLAYER_H */