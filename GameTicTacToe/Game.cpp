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