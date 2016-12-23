#pragma once
#include "stdafx.h"

#ifndef BOARD_H
#define BOARD_H

/* Generic board */
class Board
{
public:	
	virtual void Draw (void) const = 0;
	int MarkMove (void);
};

#endif