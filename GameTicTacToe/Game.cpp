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

#include "stdafx.h"
#include "Game.h"

/*
Constructor
*/
Game::Game (void)
{
	this->numberOfMoves= 0;
}

/*
Destructor
*/
Game::~Game (void)
{

}

/* 
Returns game version
*/
std::string 
Game::GetVersion (void) const
{
	return this->version;
}

/* 
Sets game version
*/
void
Game::SetVersion (std::string version)
{
	this->version= version;
}

/*
Increase internal move counter
*/
void
Game::IncreaseMovesCount (void)
{
	this->numberOfMoves++;
}

/*
Returns number of game moves
*/
int
Game::GetMovesCount (void) const
{
	return (this->numberOfMoves);
}