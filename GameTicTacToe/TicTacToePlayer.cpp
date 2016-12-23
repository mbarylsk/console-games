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