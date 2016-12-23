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
