#ifndef MAIN_CPP
#define MAIN_CPP

#include "globals.h"

void dialogueClickHandler(int x, int y, void (*yesFunction)(), void (*noFunction)())
{
	/*
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
	*/
}

void masterClickHandler(int button, int state, int x, int y)
{
	cout<<"master: x:"<<x<<" y:"<<y<<endl;
	cout<<currentState<<endl;
	//1 is clicked, not worrying about which button for the purposes of this game
	if (state == 1){

		//dependent on status, choose the correct click handler
		if (currentState == CHOOSE_LEVEL)
		{
			cout<<"in if 1"<<endl;
			introClickHandler(x,y);
		}
		else if (currentState == INSTRUCTIONS_1)
		{
			cout<<"in if 2"<<endl;
			instructionsClickHandler(x, y, 1);
		}
		else if (currentState == INSTRUCTIONS_2)
		{
			cout<<"in if 3"<<endl;
			instructionsClickHandler (x, y, 2);
		}
		else if (currentState == IN_GAME)
		{
			cout<<"in if 4"<<endl;
			inGameClickHandler(x,y);
		}
		else if (currentState == DIALOGUE_EXIT)
		{
			cout<<"in if 5"<<endl;
			dialogueClickHandler(x, y, exitGame, endDialogue);
		}
		else if (currentState == DIALOGUE_RESET)
		{
			cout<<"in if 6"<<endl;
			dialogueClickHandler(x,y, resetBoard, endDialogue);
		}
		else{
			cout<<"bleh."<<endl;
		}
	}

	cout<<"done with click handler"<<endl;
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
			cout<<"about to show instructions"<<endl;
			showInstructions(gameLevel, 1);		//that 1 tells us to show the first page of the instructions
		}
	}
	cout<<"x: "<<x<<" y: "<<y<<endl;
	cout<<"gl:"<<gameLevel<<endl;
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
/*

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
	*/
}
void gameboardClickHandler(int x, int y){
	//handle inside of the gameboard
//	gameBoard->clickHandler(x,y);
}
void dialogueBox(string name)
{
	/*
	//clear out the screen
	removeAllButGameboard();

	string assetName;
	//construct asset name based on the parameter passed in, and set the game sate
	if (name == "reset")
	{
		assetName = "reset";	
		currentState = DIALOGUE_RESET;
	}
	else if (name == "end")
	{
		assetName = "endgame";
		currentState = DIALOGUE_EXIT;
	}

	assetName += ".bmp";

	//display the dialogue screen
	overlays.push_back(framework.createSprite(assetName, 0, 0, 600, 600));
	overlays.back().setVisible(true);
	*/
}

void showInstructions(int gameLevel, int page)
{
	cout<<"here in showinstructions"<<endl;

	//clear out the screen
	removeAllButGameboard();

	string assetName;
	//construct the asset name based on the game level and the page number
	switch (gameLevel)
	{
		case 1:
			assetName = "easy_";
			break;
		case 2:
			assetName = "medium_";
			break;
		case 3:
			assetName = "hard_";
			break;
		case 4:
			assetName = "challenge_";
			break;
	}

	switch (page){
		case 1:
			assetName += "1";
			break;
		case 2:
			assetName += "2";
			break;
	}
	cout<<assetName<<endl;

	//and display it
	overlays.push_back(framework.createSprite(assetName, 0, 0, 600, 600));
	overlays.back().setVisible(true);

	//set the game state to be in the instructions state
	switch (page)
	{
		case 1:
			currentState = INSTRUCTIONS_1;
			break;
		case 2:
			currentState = INSTRUCTIONS_2;
			break;
	}
}

//remove any sprites that are currently up on the screen besides the game board
void removeAllButGameboard()
{
	while (overlays.size() > 0)
	{
		framework.removeSprite(overlays.back());
		overlays.pop_back();
	}
}

void endDialogue()
{
	/*
	//remove the dialogue box
	removeAllButGameboard();

	//reset the game state back to gameplay
	currentState = IN_GAME;
	*/
}

void updateScore()
{
	//api
}

void updateCurrentWord()
{
	/////api
}

void constructBoard(int level)
{
	//make the new gameboard dependent on the level passed in and the new user dictionary
	gameBoard = new Board(level, userDictionary);
}

void makeDictionary()
{
	//make a new user dictionary
	userDictionary = new Dictionary("dictionary.txt");
}

void beginGame()
{
/*
	//display the background
	overlays.push_back(framework.createSprite("background", 0, 0, 600, 600));
	overlays.back().setVisible(true);

	//display the gameboard
	gameBoard->displayBoard();

	//display the user score and current word text fields
	//GFText& createTextFromString(std::string, int, int, int);
	currentWord = &framework.createTextFromString("",35,535,40);
	gScore = &framework.createTextFromString("0", 490, 315, 20);

	//set the state of the game
	currentState = IN_GAME;
*/
}


void exitGame()
{
	//send the score back to the framework
	/////api

	//end game
	gameRunning = false;
}

bool returnRunning()
{
	return gameRunning;
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
	cout<<"In main"<<endl;
	GameFramework framework = GameFramework::Instance();
	//display the beginning screen
	overlays.push_back(framework.createSprite("intro", 0, 0, 600, 600));
	overlays.back().setVisible(true);
	currentState = CHOOSE_LEVEL;

	//set the correct click handler
	//this needs to be fixed to have more parameters
	framework.mouseFunc(masterClickHandler);
	cout<<"click handler declared"<<endl;
	
	//begin the game loop
	framework.gameFunc(returnRunning);
	cout<<"game function defined"<<endl;
	
	framework.gameLoop();
	cout<<"game loop exited"<< endl;

	//clean up
	overlays.back().~GFSprite();

	return 0;
}

#endif