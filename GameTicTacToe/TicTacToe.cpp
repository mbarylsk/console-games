/*  TicTacToe.cpp : main project file. */
#include "stdafx.h"
#include "TicTacToe.h"

int
main(array<System::String ^> ^args)
{
	USHORT x, y;	
	TicTacToePlayer* currentPlayer;

	/* random game starting player */
    TicTacToeGame myGame (true);

	/* artificial intelligence */
	TicTacToeAI ai;

	/* print game welcome banner and game rules*/
	myGame.PrintBanner ();
	myGame.PrintRules ();
	myGame.PrintStartScreen ();

	/* main game loop */
	while (!myGame.IsCompleted())
	{
		/* draw game board */
		myGame.Draw ();

		/* next move */		
		currentPlayer= myGame.GetCurrentPlayer ();

		/* machine */
		if (currentPlayer->IsMachine())
		{
			myGame.AICoordinates (&ai, x, y, currentPlayer);
		}
		/* human */
		else
		{
			myGame.ReadCoordinates (x, y, currentPlayer);	
		}

		/* try to move */
		switch (myGame.Move (x, y, currentPlayer))
		{
		case MOVE_SUCCESS:
			/* current move completed - change the player */
			myGame.SetNextPlayer ();
			/* move completed */
			myGame.IncreaseMovesCount ();
			break;
		case MOVE_ERROR_FIELD_OCCUPIED:
			/* field already occupied */
			std::cout << " Field already occupied. Please try another one." << std::endl << std::endl;			
			break;
		case MOVE_ERROR_X_INCORRECT:
			/* coordinates outside the board or field is already occupied */
			std::cout << " Incorrect coordinates. Please correct them. Allowed range: 0 - " << BOARD_NO_OF_ROWS- 1 << std::endl << std::endl;
			break;
		case MOVE_ERROR_Y_INCORRECT:
			/* coordinates outside the board or field is already occupied */
			std::cout << " Incorrect coordinates. Please correct them. Allowed range: 0 - " << BOARD_NO_OF_ROWS- 1 << std::endl << std::endl;
			break;
		default:
			/* in case of something else */
			std::cout << " Incorrect coordinates. Please correct them. Allowed range: 0 - " << BOARD_NO_OF_ROWS- 1 << std::endl << std::endl;
			break;
		}
	}
	
	/* display information about game winner */
	myGame.PrintEndScreen ();
	myGame.Draw();
	
	myGame.PressEnterToContinue ();

	return 0;
}
