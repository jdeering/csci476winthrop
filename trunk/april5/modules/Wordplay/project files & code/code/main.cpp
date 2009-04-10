#include <vector>
#include <string>
#include <ctime>
#include "../../../../api/GameFramework.h"
using namespace std;
enum GameStatus {CHOOSE_LEVEL, INSTRUCTIONS_1, INSTRUCTIONS_2, IN_GAME, DIALOGUE_EXIT, DIALOGUE_RESET};
GameStatus currentState = CHOOSE_LEVEL;

void masterClickHandler(int, int, int, int);
void introClickHandler(int x, int y);
bool returnRunning();
void showInstructions(int gameLevel, int page);

int main(int argc, char argv[]){
	srand(time(0));

	//display the beginning screen
	GameFramework::createSprite("intro", 0, 0, 600, 600);

	currentState = CHOOSE_LEVEL;

	//set the correct click handler
	//this needs to be fixed to have more parameters
	GameFramework::mouseFunc(masterClickHandler);
	
	//begin the game loop
	GameFramework::gameFunc(returnRunning);
	
	GameFramework::gameLoop();

	return 0;
}

void masterClickHandler(int button, int state, int x, int y)
{
	//1 is clicked, not worrying about which button for the purposes of this game
	if (state == 1){

		//dependent on status, choose the correct click handler
		if (currentState == CHOOSE_LEVEL)
		{
			introClickHandler(x,y);
		}
		else if (currentState == INSTRUCTIONS_1)
		{
			//instructionsClickHandler(x, y, 1);
		}
		else if (currentState == INSTRUCTIONS_2)
		{
			//instructionsClickHandler (x, y, 2);
		}
		else if (currentState == IN_GAME)
		{
//			inGameClickHandler(x,y);
		}
		else if (currentState == DIALOGUE_EXIT)
		{
//			dialogueClickHandler(x, y, exitGame, endDialogue);
		}
		else if (currentState == DIALOGUE_RESET)
		{
//			dialogueClickHandler(x,y, resetBoard, endDialogue);
		}
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
			cout<<"before dictionary"<<endl;
			//makeDictionary();
			cout<<"before board"<<endl;
			//constructBoard(gameLevel);
			cout<<"about to show instructions"<<endl;
			showInstructions(gameLevel, 1);		//that 1 tells us to show the first page of the instructions
		}
	}
}

bool returnRunning()
{
	return true;
	//return gameRunning;
}

void showInstructions(int gameLevel, int page)
{
	//clear out the screen
//	removeAllButGameboard();

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

	//and display it
	GameFramework::createSprite(assetName, 0, 0, 600, 600);

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