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

/* Backgammon.cpp : main project file. */
#include "stdafx.h"
#include "Backgammon.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	USHORT fromPosition, toPosition;
	BackgammonPlayer* currentPlayer;
	int moveResult;

	/* random game starting player */
    BackgammonGame myGame (true);

	/* artificial intelligence */
	BackgammonAI ai;

	/* print game welcome banner and game rules */
	myGame.PrintBanner ();
	myGame.PrintRules ();
	myGame.PrintStartScreen ();

	/* throw dice */		
	currentPlayer= myGame.GetCurrentPlayer ();
	currentPlayer->ThrowDice ();

	/* main game loop */
	while (!myGame.IsCompleted())
	{
		/* refreshes game properties */
		myGame.RefreshProperties ();

		/* draw game board */
		myGame.Draw (currentPlayer);

		/* check if any move is possible - if not, change the player */
		if (myGame.GetNumberOfPossibleMoves (currentPlayer) == 0)
		{
			myGame.PrintError (MOVE_ERROR_PLAYER_BLOCKED);			

			/* all moves done - change the player */
			myGame.SetNextPlayer ();
			currentPlayer= myGame.GetCurrentPlayer ();

			/* throw dice */
			currentPlayer->ThrowDice ();

			/* game move completed */
			myGame.IncreaseMovesCount ();

			/* skip this loop */
			continue;
		}

		/* machine */
		if (currentPlayer->IsMachine())
		{
			myGame.AICoordinates (&ai, fromPosition, toPosition, currentPlayer);
		}
		/* human */
		else
		{
			myGame.ReadCoordinates (fromPosition, toPosition, currentPlayer);	
		}

		/* try to move */
		moveResult= myGame.Move (fromPosition, toPosition, currentPlayer);
		switch (moveResult)
		{
		case MOVE_SUCCESS:
			/* current move completed - are there any moves left for the player? */
			if (myGame.GetNumberOfPossibleMoves (currentPlayer) == 0)
			{
				/* all moves done - change the player */
				myGame.SetNextPlayer ();
				currentPlayer= myGame.GetCurrentPlayer ();

				/* throw dice */
				currentPlayer->ThrowDice ();
			}
			/* move completed */
			myGame.IncreaseMovesCount ();
			break;
		default:
			myGame.PrintError (moveResult);
			break;
		}
	}
}
