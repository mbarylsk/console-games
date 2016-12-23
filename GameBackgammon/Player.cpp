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