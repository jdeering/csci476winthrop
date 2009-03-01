#ifndef CLICKHANDLERS_CPP
#define CLICKHANDLERS_CPP
#include "globals.cpp"
#include "showhide.cpp"
#include "main.cpp"

void masterClickHandler(int x, int y)
{
	//dependent on status, choose the correct click handler
	if (currentState == CHOOSE_LEVEL)
	{
		introClickHandler(x,y);
	}
	else if (currentState == INSTRUCTIONS_1)
	{
		instructionsClickHandler(x, y, 1);
	}
	else if (currentState == INSTRUCTIONS_2)
	{
		instructionsClickHandler (x, y, 2);
	}
	else if (currentState == IN_GAME)
	{
		inGameClickHandler(x,y);
	}
	else if (currentState == DIALOGUE_EXIT)
	{
		dialogueClickHandler(x, y,&exitGame,&endDialogue);
	}
	else if (currentState == DIALOGUE_RESET)
	{
		dialogueClickHandler(x,y,&resetBoard,&endDialogue);
	}
}


void introClickHandler(int x, int y)
{

	//this will hold the game level the user selects
	int gameLevel = -1;

	//if it's in the right y-value for a level button
	if(y > 400 && y < 575)
	{

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

		//as long as they clicked on a level button
		if (gameLevel != -1){
			//go ahead and show instructions for that level

			//construct the gameboard and the dictionary
			makeDictionary();
			constructBoard(gameLevel);

			showInstructions(gameLevel, 1);		//that 1 tells us to show the first page of the instructions
		}
	}
}

void instructionsClickHandler(int x, int y, int instructionsPage){
	//if we're on the second instructions page, there's a begin game and previous page button
	if (instructionsPage == 2){	
		//if it's the begin game button	
		if(x > 335 && x < 550 && y > 505 && y < 550)
		{
			beginGame();
		}

		//if it's the previous button
		else if(x > 40 && x < 170 && y > 505 && y < 550)
		{
			showInstructions(gameBoard->returnLevel(), 1);
		}
	}

	//if we're on the first instructions page, there's a next button
	else{
		//if it's the 'next' button
		if (x > 420 && x < 545 && y > 505 && y < 550)
		{
			showInstructions(gameBoard->returnLevel(), 2);
		}
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

void gameboardClickHandler(int x, int y){
	//handle inside of the gameboard
	gameBoard->clickHandler(x,y);
}
#endif