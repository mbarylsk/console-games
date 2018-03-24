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
#include "Player.h"

/*
Constructor
*/
Player::Player (bool machine, int color, bool active)
{
	this->machine= machine;
	this->color= color;
	this->active= active;
}

/*
Destructor
*/
Player::~Player(void)
{

}

/* 
Returns color of the player
*/
int
Player::GetColor (void) const
{
	return this->color;
}

/*
Returns true if player is machine (computer)
Returns false if player is a human
*/
bool
Player::IsMachine (void) const
{
	return this->machine;
}

/*
Returns true if player is active
Returns false if player is not active
*/
bool
Player::IsActive (void) const
{
	return this->active;
}

/*
Sets player inactive
*/
void
Player::MakeActive (void) 
{
	this->active= true;
}

/*
Sets player active
*/
void
Player::MakeInactive (void) 
{
	this->active= false;
}
