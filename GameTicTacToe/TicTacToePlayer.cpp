#include "stdafx.h"
#include "TicTacToePlayer.h"

/*
Constructor
*/
TicTacToePlayer::TicTacToePlayer (BOARD_CELL_STATE mark, bool machine, int color, bool active):
Player (machine, color, active)
{
	this->mark= mark;
}

/*
Destructor
*/
TicTacToePlayer::~TicTacToePlayer(void)
{

}

/*
Gets player mark
*/
BOARD_CELL_STATE
TicTacToePlayer::GetMark (void) const
{
	return (this->mark);
}

/*
Prints information about player
*/
void
TicTacToePlayer::PrintName (void) const
{
	HANDLE hConsole;
					
	hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);

	SetConsoleTextAttribute(hConsole, this->GetColor());  
	std::cout << "Player" << this->GetMark();

	/* sets color to white */
	SetConsoleTextAttribute(hConsole, WHITE);
}

/*
Prints player mark
*/
void
TicTacToePlayer::PrintMark (void) const
{
	HANDLE hConsole;
					
	hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);

	SetConsoleTextAttribute(hConsole, this->GetColor());
	switch (this->GetMark())
	{
	case O:
		std::cout << "o";
		break;
	case X:
		std::cout << "x";
		break;
	default:
		break;
	}

	/* sets color to white */
	SetConsoleTextAttribute(hConsole, WHITE);
}