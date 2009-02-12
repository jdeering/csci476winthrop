#include <string>

#include "Board.h"
#include "Tile.h"
#include "Dictionary.h"

enum GameStatus {CHOOSE_LEVEL, INSTRUCTIONS, IN_GAME};
GameStatus currentStatus;

Board * gameBoard;
int gameLevel;

//function prototypes

//hide and show functions for beginning of game
void showSetLevelDialogue();
void hideSetLevelDialogue();
void showInstructions(int);
void hideInstructions();

//setup functions
void setupGame();

//click handlers
void clickHandler(int, int);
void clickSubmit();
void clickReset();
void clickEnd();

//////////////////////////////////////////
//	beginning the game					//
//////////////////////////////////////////

void showSetLevelDialogue()
{
	//show the user a choice of levels with explanations of the rules

	//change game status to let us know that we're choosing the level
	currentStatus = CHOOSE_LEVEL;

}

void hideSetLevelDialogue(){
	//when the user clicks a level, we want to take away the dialogue box

	//show instruction screen


}

void showInstructions(){
	//dependent on level, show text and picture instructions for the game


	//place a button that lets the user begin the game
	currentStatus = INSTRUCTIONS;
}

void hideInstructions(){

	//hide the instruction screen



	currentStatus = IN_GAME;

}

//////////////////////////////////////////
//	gameplay setup			//
//////////////////////////////////////////

void setupGame()
{

	//set up dictionary
	Dictionary userDictionary("");

	//make the gameboard
	gameBoard = new Board(gameLevel, &userDictionary);

	//set up layout of everything on screen

}

//////////////////////////////////////////
//	click functions						//
//////////////////////////////////////////

void clickHandler(int x, int y)
{

	//figure out where we've clicked and send it to an appropriate handler
	//the clickable items will depend on where we are in gameplay


	//during choosing a level
	if(currentStatus == CHOOSE_LEVEL)
	{
		//if it's a level button
		if(y > 400 && y < 575)
		{
			//hide the dialogue box
			hideSetLevelDialogue();

			//decide which level it is, and select that level
			if(x > 20 && x < 145)
			{
				gameLevel = 1;
			}
			else if (x > 165 && x < 290)
			{
				gameLevel = 2;
			}
			else if (x > 310 && x < 435)
			{
				gameLevel = 3;
			}

			else if (x > 455 && x < 580)
			{
				gameLevel = 4;
			}
			//go ahead and show instructions for that level
			showInstructions();
		}

	}
			
	//during instructions
	else if (currentStatus == INSTRUCTIONS)
	{	
		//if it's the begin game button	
		if()
		{
			//hide the instructions and begin gameplay
			hideInstructions();
			setupGame();
		}

	}

	//during gameplay
	else if (currentStatus == IN_GAME)
	{
	
		//if it's anywhere in the board, let it be handled there
		if(x >= 25 && x <= 475 && y > 25 && y <=475)
		{
			gameBoard->clickHandler(x,y);
		}

		//if it's the submit word button
		else if(x > 475 && x < 575 && y > 525 && y < 575)
		{

			//check to see if the word is valid

			//if it is
			if(gameBoard->isWord())
			{
				//submit the word
				//replace the tiles on the board and take care of
				//resetting any other variables on the board
				gameBoard->submitWord();
				
			}
	
			//otherwise ignore it, we don't need to submit the word
		}
		
		//if it's the reset board button
		else if(x > 510 && x < 590 && y > 130 && y < 160)
		{
			clickReset();
		}

		//if it's the end game button
		else if (x > 510 && x < 590 && y > 180 && y < 210)
		{
			clickEnd();
		}

	}
}

void clickSubmit()
{
	//check to see if this button is enabled

	//if it is, we have a valid word
			
		//score it and add to score

		//update the score on the interface

		//remove those tiles from the board, and replace them

	//if not, ignore the click

		//might need to do something for usability here to make it clear that it's not a valid word
}

void clickReset()
{
	//ask if you're sure you want to reset

		//if yes, reset the board

		//give score penalty

		
		//if not, don't worry about it

}

void clickEnd()
{
	//ask if you're sure you want to end

	//if yes, send score back to framework and exit

	//if no, go back to game
}
