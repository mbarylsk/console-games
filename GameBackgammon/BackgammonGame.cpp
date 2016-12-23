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
#include "BackgammonGame.h"

/*
Constructor
responsible for preparing initial board and setting the players
*/
BackgammonGame::BackgammonGame (bool isLottery)
{
	int i;
	bool isHumanStarting= true;
	BackgammonPlayer* ptr;

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
			ptr= new BackgammonPlayer (true, RED, !isHumanStarting);
		}
		/* player 2: human */
		else if (i == 1)
		{
			ptr= new BackgammonPlayer (false, YELLOW, isHumanStarting);
		}
		/* no more players allowed for now */
		else
		{
			break;
		}
		this->players[i]= ptr;
	}

	/* tokens are not separated */
	this->board.SetTokensSeparation (false);

	/* no winner yet */
	this->winner= 0;
}

/*
Destructor
*/
BackgammonGame::~BackgammonGame (void)
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
Refreshes game properties
*/
void BackgammonGame::RefreshProperties (void)
{
	USHORT i;

	for (i= 0; i < NUMBER_OF_COLORS; i++)
	{
		if (this->board.CheckIfAllTokensInFinishQuarter (i))
		{
			this->board.SetTokensAtFinalQuarter (true, i);
		}
		else
		{
			this->board.SetTokensAtFinalQuarter (false, i);
		}
	}
	if (this->board.CheckIfTokensAreSeparated())
	{
		this->board.SetTokensSeparation (true);
	}
}

/* 
Checks if game is already completed
Complete crtiterion - one of the player has removed all the token from the board
*/
bool
BackgammonGame::IsCompleted ()
{
	if ((this->board.GetTokensLeft(0) == 0) || (this->board.GetTokensLeft(1) == 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
Checks if given player has done all his moves
*/
bool
BackgammonGame::ArePlayerMovesDone (BackgammonPlayer* player)
{
	/* check if are any dice available */
	if ((player->GetDice(DICE_ONE) == 0) && (player->GetDice(DICE_TWO) == 0))
	{
		return true;
	}

	/* check if there is any more move possible */
	if (GetNumberOfPossibleMoves (player) == 0)
	{
		return true;
	}

	return false;
}

/*
Returns number of possible moves that the player can still do
Returns 0 if no more moves are possible
*/
UINT
BackgammonGame::GetNumberOfPossibleMoves (BackgammonPlayer* player)
{
	BackgammonBoard* futureBoard;
	USHORT end;
	int playerColorNo;
	UINT number= 0;
	int i, j;

	/* if all dice used, no more moves are possible */
	if ((player->GetDice(DICE_ONE) == 0) && (player->GetDice(DICE_TWO) == 0) && (player->GetDice(DICE_ONE_DOUBLE) == 0) && (player->GetDice(DICE_TWO_DOUBLE) == 0))
	{
		return 0;
	}
	
	playerColorNo = player->GetNumber();

	/* case 1: go through all the regular fields - only if there are no tokens left at home */
	if (this->board.GetTokensAtHome(playerColorNo) == 0)
	{
		/* machine */
		if (player->IsMachine())
		{
			for (i= NUMBER_OF_FIELDS- 1; i >= 0; i--)
			{		
				for (j= 0; j < DICE_NUMBER; j++)
				{			
					if (player->GetDice(j) > 0)
					{
						futureBoard= this->board.Clone ();

						end= NUMBER_OF_FIELDS- player->GetDice(j)- 1;	
						if (futureBoard->MarkMove (i, end, playerColorNo) == MOVE_SUCCESS)
						{
							number++;
						}

						free (futureBoard);
						futureBoard= NULL;
					}
				}
			}
		}
		/* human */
		else
		{
			for (i= 0; i < NUMBER_OF_FIELDS; i++)
			{		
				for (j= 0; j < DICE_NUMBER; j++)
				{			
					if (player->GetDice(j) > 0)
					{
						futureBoard= this->board.Clone ();

						end= i+ player->GetDice(j);				
						if (futureBoard->MarkMove (i, end, playerColorNo) == MOVE_SUCCESS)
						{
							number++;
						}

						free (futureBoard);
						futureBoard= NULL;
					}
				}
			}
		}
		/* TO DO */
		/* case 2: tokens at final quarter */
		if (this->board.CheckIfAllTokensInFinishQuarter (playerColorNo))
		{
			/* machine */
			if (player->IsMachine())
			{

			}
			/* human */
			else
			{
				for (i= NUMBER_OF_FIELDS-6; i < NUMBER_OF_FIELDS; i++)
				{		
					for (j= 0; j < DICE_NUMBER; j++)
					{			
						if (player->GetDice(j) > 0)
						{							
							end= i+ player->GetDice(j);
							if (end > NUMBER_OF_FIELDS)
							{
								futureBoard= this->board.Clone ();
								if (futureBoard->MarkMove (i, BOARD_FINISH_VALUE- 1, playerColorNo) == MOVE_SUCCESS)
								{
									number++;
								}
								free (futureBoard);
								futureBoard= NULL;
							}
						}
					}
				}
			}
		}
	}
	/* case 3: some tokens at base */
	else
	{
		/* both human and machine */
		for (i= 0; i < DICE_NUMBER; i++)
		{			
			futureBoard= this->board.Clone ();
			if (player->IsMachine())
			{
				end= NUMBER_OF_FIELDS- player->GetDice(i);
			}
			else
			{
				end= player->GetDice(i)+ 1;
			}
			if (futureBoard->MarkMove (BOARD_HOME_VALUE, end, playerColorNo) == MOVE_SUCCESS)
			{
				number++;
			}
			free (futureBoard);
			futureBoard= NULL;
		}
	}

	return number;
}

/*
Makes move for a given player
*/
int
BackgammonGame::Move (USHORT oldPosition, USHORT newPosition, BackgammonPlayer* player)
{
	int result= 0;
	USHORT absoluteMove= 0;
	bool moveInsideBoard= true;

	/* machine */
	if (player->IsMachine ())
	{
		if (this->board.GetTokensAtHome(PLAYER_MACHINE) > 0)
		{
			if (oldPosition != BOARD_HOME_VALUE)
			{
				return MOVE_ERROR_USE_HOME_FIRST;
			}			
			else
			{
				absoluteMove= BOARD_HOME_VALUE- newPosition;
			}
		}
		else
		{
			if (oldPosition < newPosition)
			{
				return MOVE_ERROR_INCORRECT_DIRECTION;
			}
			else if (newPosition == oldPosition)
			{
				return MOVE_ERROR_NO_MOVE;
			}
			else if (newPosition == BOARD_FINISH_VALUE)
			{
				moveInsideBoard= false;
				absoluteMove= oldPosition- newPosition;
			}
			else
			{
				absoluteMove= oldPosition- newPosition;
			}
		}
	}
	/* human */
	else
	{
		if (this->board.GetTokensAtHome(PLAYER_HUMAN) > 0)
		{
			if (oldPosition != BOARD_HOME_VALUE)
			{
				return MOVE_ERROR_USE_HOME_FIRST;
			}
			else
			{
				absoluteMove= newPosition+ 1;
			}
		}
		else
		{
			if (newPosition < oldPosition)
			{
				return MOVE_ERROR_INCORRECT_DIRECTION;
			}
			else if (newPosition == oldPosition)
			{
				return MOVE_ERROR_NO_MOVE;
			}
			else if (newPosition == BOARD_FINISH_VALUE)
			{				
				moveInsideBoard= false;
				absoluteMove= newPosition- oldPosition- 1;
			}
			else
			{
				absoluteMove= newPosition- oldPosition;
			}
		}
	}

	/* check if such move is possible */
	if (!player->CheckIfDiceCombinationIsAvailable (absoluteMove, moveInsideBoard))
	{
		return MOVE_ERROR_NO_SUCH_DICE_AVAILABLE;
	}

	/* try to make this move */
	if (player->IsMachine())
	{
		result= this->board.MarkMove (oldPosition, newPosition, PLAYER_MACHINE);
	}
	else
	{
		result= this->board.MarkMove (oldPosition, newPosition, PLAYER_HUMAN);
	}

	/* use dice if move done */
	/* otherwise do not touch dice */
	if (MOVE_SUCCESS == result)
	{
		player->UseDice(absoluteMove);
	}

	/* check if tokens are separated */
	if (!this->board.GetTokensSeparation())
	{
		this->board.SetTokensSeparation(this->board.CheckIfTokensAreSeparated ());
	}

	/* inform about final move result */
	return result;
}

/*
Calculates next move for machine
*/
void
BackgammonGame::AICoordinates (BackgammonAI* ai, USHORT &oldPosition, USHORT &newPosition, BackgammonPlayer* player)
{
	USHORT startPosition, endPosition;
	char letter;

	/* AI calculates coordinates of the best possible move */
	ai->FindBestMove (&board, startPosition, endPosition, player);
	oldPosition= startPosition;
	newPosition= endPosition;

	/* display the values */
	std::cout << std::endl;

	letter = this->TranslateCoordinateToLetter (oldPosition);
	player->PrintName();
	std::cout << ": Get start coordinate: " << letter << std::endl;

	letter = this->TranslateCoordinateToLetter (newPosition);
	player->PrintName();
	std::cout << ": Get end coordinate:   " << letter << std::endl;

	std::cout << std::endl;
}

/*
Gets next move details from human
*/
void
BackgammonGame::ReadCoordinates (USHORT &oldPosition, USHORT &newPosition, BackgammonPlayer* player) const
{
	std::string value;

	/* read coordinates of the next move */
	std::cout << std::endl;

	player->PrintName();
	std::cout << ": Get start coordinate: ";
	std::cin >> value;

	oldPosition= this->TranslateLetterToCoordinate (value);

	player->PrintName();
	std::cout << ": Get end coordinate:   ";
	std::cin >> value;

	newPosition= TranslateLetterToCoordinate (value);

	std::cout << std::endl;
}

/*
Translates integer coordinate to letter
*/
char
BackgammonGame::TranslateCoordinateToLetter (USHORT value) const
{
	if ( (value >= 0) && (value < NUMBER_OF_LETTERS) )
	{
		return LETTER[value];
	}
	else
	{
		return NULL;
	}	
}

/*
Translates letter to integer coordinate 
*/
USHORT
BackgammonGame::TranslateLetterToCoordinate (std::string letter) const
{
	USHORT i;

	for (i= 0; i < NUMBER_OF_LETTERS; i++)
	{
		/* letter was found */
		if ( toupper(letter[0]) == LETTER[i] )
		{
			return i;
		}
	}

	/* nothing found */
	return ERROR_WRONG_LETTER;
}

/*
Sets next player
*/
void
BackgammonGame::SetNextPlayer (void)
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
Returns current player
*/
BackgammonPlayer* 
BackgammonGame::GetCurrentPlayer (void) const
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
Gets a winner
*/
BackgammonPlayer*
BackgammonGame::GetWinner(void) const
{
	return this->winner;
}

/*
Draws game
*/
void
BackgammonGame::Draw (BackgammonPlayer* currentPlayer) const
{
	board.Draw(currentPlayer);
}

/*
Prints game main banner
*/
void
BackgammonGame::PrintBanner () const
{
	HANDLE hConsole;
					
	hConsole= GetStdHandle(STD_OUTPUT_HANDLE);  

	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << std::endl;
	std::cout << "+-----------------------------------+" << std::endl;
	std::cout << "|       ";
	FlushConsoleInputBuffer(hConsole);     
	SetConsoleTextAttribute(hConsole, RED);  
	std::cout << "Back";
	FlushConsoleInputBuffer(hConsole);     
	SetConsoleTextAttribute(hConsole, YELLOW);  
	std::cout << "gammon";
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " v. " << GAME_VERSION << "      |" << std::endl;
	std::cout << "+-----------------------------------+" << std::endl;
	std::cout << std::endl;
}

/*
Prints game rules
*/
void
BackgammonGame::PrintRules () const
{
	std::cout << "GAME RULES:" << std::endl;
	std::cout << std::endl;
	std::cout << "There are two players in the game:" << std::endl << std::endl;

	this->players[1]->PrintName();
	std::cout << "     - you";
	std::cout << std::endl;

	this->players[0]->PrintName();
	std::cout << "- your opponent";
	std::cout << std::endl << std::endl;

	std::cout << "Starting player is chosen randomly." << std::endl;

	std::cout << "Each turn each player moves his tokens toward finish zone: human from A to Z," << std::endl << "computer from X to A. ";
	std::cout << "Move length is determined by dice values. Players throw" << std::endl << "two dice at the beginning of each turn. ";
	std::cout << "If dice are duplicated, four values are available. Move on board may be combined from one, two, three, or four values." << std::endl;
	std::cout << "Move is possible if at the source there is at least one player's token and at" << std::endl << "the destination there is zero or one opponent's token. ";
	std::cout << "Single opponent's token" << std::endl << "is hit and returns back to home base. Before any further move on board player" << std::endl << "must deploy all tokens from the home to the board. ";
	std::cout << "It can happen that all" << std::endl << "potential moves are blocked and player cannot move - in this case his turn is" << std::endl << "lost.";

	std::cout << std::endl << std::endl;
	std::cout << "Win criterion: Player removed all tokens from the board." << std::endl;

	PrintHorizontalLine ();
	std::cout << std::endl;
}

void
BackgammonGame::PrintStartScreen (void) const
{
	BackgammonPlayer* player;
	player= GetCurrentPlayer();

	std::cout << "START OF THE GAME:" << std::endl;
	std::cout << std::endl;
	player->PrintName();
	if (player->GetNumber() == PLAYER_HUMAN)
	{
		std::cout << "start the game.";
	}
	else
	{
		std::cout << "starts the game.";
	}
	std::cout << std::endl << std::endl;
	PrintHorizontalLine ();
	std::cout << std::endl;
}

void
BackgammonGame::PrintHorizontalLine (void) const
{
	int i;
	for (i= 0; i < GAME_SCREEN_WIDTH; i++)
	{
		std::cout << "-";
	}
	std::cout << std::endl;
}

void
BackgammonGame::PrintError (int error) const
{
	HANDLE  hConsole;

	hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);     
	SetConsoleTextAttribute(hConsole, BLUE);

	switch (error)
	{
		case MOVE_ERROR_NO_SUCH_DICE_AVAILABLE:
			/* wrong coordinates */
			std::cout << " Such move is not possible. Try another one." << std::endl << std::endl;
			break;
		case MOVE_ERROR_USE_HOME_FIRST:
			/* wrong coordinates */
			std::cout << " Move tokens at home first." << std::endl << std::endl;
			break;
		case MOVE_ERROR_INCORRECT_DIRECTION:
			/* wrong coordinates */
			std::cout << " Move tried in incorrect direction." << std::endl << std::endl;
			break;
		case MOVE_ERROR_NO_MOVE:
			/* wrong coordinates */
			std::cout << " No move. Source and destination field must not be the same." << std::endl << std::endl;
			break;
		case MOVE_ERROR_TOKENS_LEFT_AT_HOME:
			/* wrong coordinates */
			std::cout << " This move cannot be done. Still some tokens are left at home - move them first." << std::endl << std::endl;
			break;
		case MOVE_ERROR_NO_TOKENS_AVAILABLE:
			/* wrong coordinates */
			std::cout << " No tokens available at the source field." << std::endl << std::endl;
			break;
		case MOVE_ERROR_FIELD_ALREADY_OCCUPIED:
			/* wrong coordinates */
			std::cout << " Destination field is occupied by 2+ opponent's tokens." << std::endl << std::endl;
			break;
		case MOVE_ERROR_CANNOT_FINISH_YET:
			/* wrong coordinates */
			std::cout << " Cannot remove the token yet. Not all tokens are moved to the final quarter." << std::endl << std::endl;
			break;
		case MOVE_ERROR_PLAYER_BLOCKED:
			/* player cannot move because is blocked */
			std::cout << " Player is blocked and cannot move. Changing player." << std::endl << std::endl;
			break;
		default:
			/* Unknown error */
			std::cout << " Unrecognized error." << std::endl << std::endl;
			break;
	}

	SetConsoleTextAttribute(hConsole, WHITE);
}