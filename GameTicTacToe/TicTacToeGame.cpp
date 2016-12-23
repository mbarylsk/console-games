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

#include "stdafx.h"
#include "TicTacToeGame.h"
#include "TicTacToeAI.h"

/*
Constructor
responsible for preparing empty board and setting the players
*/
TicTacToeGame::TicTacToeGame (bool isLottery)
{
	int i;
	bool isHumanStarting= true;
	TicTacToePlayer* ptr;

	/* random starter - either human or computer */
	if (isLottery)
	{
		/* initialize random seed */
		srand ( (unsigned int)time(NULL) );

		/* lottery */
		i= rand () % 2;
		switch (i)
		{
		case 0:
			isHumanStarting= true;
			break;
		case 1:
			isHumanStarting= false;
			break;
		default:
			isHumanStarting= true;
			break;
		}
	}

	/* set game version */
	this->SetVersion (GAME_VERSION);

	/* create game players */
	for (i= 0; i < NUMBER_OF_PLAYERS; i++)
	{
		/* player 1: machine */
		if (i == 0)
		{
			ptr= new TicTacToePlayer (X, true, RED, !isHumanStarting);
		}
		/* player 2: human */
		else if (i == 1)
		{
			ptr= new TicTacToePlayer (O, false, YELLOW, isHumanStarting);
		}
		/* no more players allowed for now */
		else
		{
			break;
		}
		this->players[i]= ptr;
	}

	/* no winner yet */
	this->winner= 0;
}

/*
Destructor
*/
TicTacToeGame::~TicTacToeGame (void)
{
	int i;

	/* delete players */
	for (i= 0; i < NUMBER_OF_PLAYERS; i++)
	{
		delete (players[i]);
		players[i]= 0;
	}
}

/*
Returns player with the given mark
*/
TicTacToePlayer*
TicTacToeGame::GetPlayerWithMark (BOARD_CELL_STATE mark) const
{
	int i;

	/* go through all players in the game - their marks should be unique */
	for (i= 0; i < NUMBER_OF_PLAYERS; i++)
	{
		if (players[i]->GetMark() == mark)
		{
			return players[i];
		}
	}

	/* nothing found */
	return 0;
}

/* 
Checks if game is already completed
*/
bool
TicTacToeGame::IsCompleted ()
{
	TicTacToePlayer* player;
	BOARD_CELL_STATE winnerMark;

	winnerMark= board.GetWinner ();
	player= GetPlayerWithMark (winnerMark);

	if ((player != 0))
	{
		/* We got a winner */
		this->winner= player;
		/* Game completed */
		return true;
	}
	else if (board.IsFull())
	{
		/* Board full and nobody won - we have a draw */
		this->winner= 0;
		/* Game completed */
		return true;
	}
	else if (!board.IsWinPossible())
	{
		/* Draw - nobody won */
		this->winner= 0;
		/* It is not possible to win this game
		there is no point in continuing it even if some fields are empty */
		return true;
	}
	else
	{
		/* No winner and game not completed yet */
		this->winner= 0;
		return false;
	}
}

/*
Sets the next player
*/
void
TicTacToeGame::SetNextPlayer()
{
	if (players[0]->IsActive())
	{
		players[0]->MakeInactive();
		players[1]->MakeActive();
	}
	else
	{
		players[0]->MakeActive();
		players[1]->MakeInactive();
	}
}

/*
Gets a winner
*/
TicTacToePlayer*
TicTacToeGame::GetWinner(void) const
{
	return this->winner;
}

/*
Gets a current player
*/
TicTacToePlayer*
TicTacToeGame::GetCurrentPlayer(void) const
{
	int i;

	/* go through players */
	for (i= 0; i < NUMBER_OF_PLAYERS; i++)
	{
		if (players[i]->IsActive())
		{
			return (players[i]);
		}
	}

	/* nothing found */
	return 0;
}

/*
Draws game graphics
*/
void
TicTacToeGame::Draw (void) const
{
	board.Draw();
}

/*
Do move on board
*/
int
TicTacToeGame::Move (USHORT x, USHORT y, TicTacToePlayer* player)
{
	return (board.MarkMove(x, y, player->GetMark()));
}

/*
Reads X and Y coordinates from the input
*/
void
TicTacToeGame::ReadCoordinates (USHORT &rx, USHORT &ry, TicTacToePlayer* player) const
{
	USHORT value;

	/* read coordinates of the next move */
	std::cout << std::endl;

	player->PrintName();
	std::cout << ": Get X coordinate (0-2): ";
	while(!(std::cin >> value))
	{
		std::cin.clear ();
		std::cin.ignore (BOARD_NO_OF_ROWS- 1, '\n');
	}
	rx= value;

	player->PrintName();
	std::cout << ": Get Y coordinate (0-2): ";
	while(!(std::cin >> value))
	{
		std::cin.clear ();
		std::cin.ignore (BOARD_NO_OF_ROWS- 1, '\n');
	}
	ry= value;

	std::cout << std::endl;
}

/*
Calculates the AI coordinates
*/
void
TicTacToeGame::AICoordinates (TicTacToeAI* ai, USHORT &rx, USHORT &ry, TicTacToePlayer* player)
{
	USHORT x, y;

	/* AI calculates coordinates of the best possible move */
	ai->FindBestMove (&board, x, y, player->GetMark());
	rx= x;
	ry= y;

	/* display the values */
	std::cout << std::endl;

	player->PrintName();
	std::cout << ": Get X coordinate (0-2): " << x << std::endl;

	player->PrintName();
	std::cout << ": Get Y coordinate (0-2): " << y << std::endl;

	std::cout << std::endl;
}

/*
Prints game main banner
*/
void
TicTacToeGame::PrintBanner () const
{
	HANDLE hConsole;

	hConsole= GetStdHandle(STD_OUTPUT_HANDLE);  

	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << std::endl;
	std::cout << "+-----------------------------------+" << std::endl;
	std::cout << "|       ";
	FlushConsoleInputBuffer(hConsole);     
	SetConsoleTextAttribute(hConsole, RED);  
	std::cout << "Tic";
	FlushConsoleInputBuffer(hConsole);     
	SetConsoleTextAttribute(hConsole, YELLOW);  
	std::cout << " Tac";
	FlushConsoleInputBuffer(hConsole);     
	SetConsoleTextAttribute(hConsole, RED);  
	std::cout << " Toe";
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " v. " << GAME_VERSION << "     |" << std::endl;
	std::cout << "+-----------------------------------+" << std::endl;
	std::cout << std::endl;
}

/*
Prints game rules
*/
void
TicTacToeGame::PrintRules () const
{
	std::cout << "GAME RULES:" << std::endl;
	std::cout << std::endl;
	std::cout << "There are two players in the game:" << std::endl << std::endl;

	this->players[1]->PrintName();
	std::cout << " - ";
	this->players[1]->PrintMark();
	std::cout << " - human (you)";
	std::cout << std::endl;

	this->players[0]->PrintName();
	std::cout << " - ";
	this->players[0]->PrintMark();
	std::cout << " - computer (your opponent)";
	std::cout << std::endl << std::endl;

	std::cout << "Starting player is chosen randomly." << std::endl;
	std::cout << "Each turn each player puts his unique mark in the empty field.";

	std::cout << std::endl << std::endl;
	std::cout << "Win criterion: " << BOARD_LENGTH_OF_WINNING_LINE << " identical symbols in a row or diagonally." << std::endl;
	std::cout << "Draw criteria: further moves cannot lead to the victory or all fields occupied." << std::endl;
	std::cout << std::endl << std::endl;
}

/*
Prints start screen, with starting player
*/
void
TicTacToeGame::PrintStartScreen (void) const
{
	TicTacToePlayer* player;
	player= GetCurrentPlayer();

	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "START OF THE GAME:" << std::endl;
	std::cout << std::endl << std::endl;
	player->PrintName();
	std::cout << " starts the game.";
	std::cout << std::endl << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
}

/*
Prints end screen, with game summary
*/
void
TicTacToeGame::PrintEndScreen (void) const
{
	TicTacToePlayer* player;
	int numberOfMoves;

	player= GetWinner ();
	numberOfMoves= GetMovesCount ();

	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "END OF THE GAME:" << std::endl;
	std::cout << std::endl << std::endl;

	if (player == 0)
	{
		std::cout << "No winners - we have a draw.";
	}
	else
	{
		std::cout << "And the winner is ";
		player->PrintName();
		std::cout << ".";
	}
	std::cout << std::endl << "Number of moves: " << numberOfMoves << ".";

	std::cout << std::endl << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
}

/*
Prints info about pressing Enter to continue; waits until Enter is pressed
*/
void
TicTacToeGame::PressEnterToContinue (void) const
{
	std::cout << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "Press ENTER to continue ..." << std::endl;

	std::cin.ignore ();
	std::cin.get ();
}
