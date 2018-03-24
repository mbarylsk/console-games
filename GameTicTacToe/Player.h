/*
Copyright(C) 2012-2018  Marcin Barylski

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