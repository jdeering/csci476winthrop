#ifndef MAIN_CPP
#define MAIN_CPP

#include "globals.h"

void dialogueClickHandler(int x, int y, void (*yesFunction)(), void (*noFunction)())
{
	//if the user clicks yes
	if (x > 50 && x < 200 && y < 400 && y > 450 )
	{
		//call the yes function
		yesFunction();
	}

	//if the user clicks no
	else if (x > 300 && x < 450 && y > 400 && y < 450)
	{
		//call the no function
		noFunction();
	}
}








void inGameClickHandler(int x, int y)
{
	//if it's anywhere in the board, let it be handled there
	if(x >= 25 && x <= 475 && y > 25 && y <=475)
	{
		gameboardClickHandler(x,y);
	}

	//if it's the submit word button
	else if(x > 475 && x < 575 && y > 525 && y < 575)
	{
		//let the board class handle it through this function
		submitWord();
	}
	
	//if it's the reset board button
	else if(x > 510 && x < 590 && y > 130 && y < 160)
	{
		dialogueBox("reset");
	}

	//if it's the end game button
	else if (x > 510 && x < 590 && y > 180 && y < 210)
	{
		dialogueBox("end");
	}
}
void gameboardClickHandler(int x, int y){
	//handle inside of the gameboard
	gameBoard->clickHandler(x,y);
}
void dialogueBox(string name)
{
	//clear out the screen
	removeAllButGameboard();

	string assetName;
	//construct asset name based on the parameter passed in, and set the game state
	if (name == "reset")
	{
		assetName = "reset";	
		currentState = DIALOGUE_RESET;
	}
	else if (name == "end")
	{
		assetName = "end";
		currentState = DIALOGUE_EXIT;
	}

	//display the dialogue screen
	overlays.push_back(GameFramework::createSprite(assetName, 0, 0, 600, 600));
	overlays.back().setVisible(true);
}



//remove any sprites that are currently up on the screen besides the game board
void removeAllButGameboard()
{
	while (overlays.size() > 0)
	{
		GameFramework::removeSprite(overlays.back());
		overlays.pop_back();
	}
}

void endDialogue()
{
	////////////problem here?
	//remove the dialogue box
	removeAllButGameboard();

	//reset the game state back to gameplay
	currentState = IN_GAME;
}

void updateScore()
{
	//api
}

void updateCurrentWord()
{
	/////api
}




void exitGame()
{
	//send the score back to the framework
	/////api

	//end game
	gameRunning = false;
}

void resetBoard()
{
	///**** not implemented yet

	//reset the board 
	//gameBoard->reset();

	//update the score
	score = score - 50;

	//update the score and current word
	updateScore();
	updateCurrentWord();
}


void submitWord()
{
/*
	//submit and score the word
	int wordScore;
	wordScore = gameBoard->submitWord();

	//add to the current score
	score = score + wordScore;

	//update the score and current word
	updateScore();
	updateCurrentWord();
*/
}




































int main(int argc, char argv[]){
	srand(time(0));

	//display the beginning screen
	GameFramework::createSprite("intro", 0, 0, 600, 600);

//	overlays.push_back(GameFramework::createSprite("intro", 0, 0, 600, 600));
//	overlays.back().setVisible(true);
	currentState = CHOOSE_LEVEL;

	//set the correct click handler
	//this needs to be fixed to have more parameters
	GameFramework::mouseFunc(masterClickHandler);
	
	//begin the game loop
	GameFramework::gameFunc(returnRunning);
	
	GameFramework::gameLoop();

	//clean up
	overlays.back().~GFSprite();

	return 0;
}

#endif