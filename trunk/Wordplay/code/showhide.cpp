#ifndef SHOWHIDE_CPP
#define SHOWHIDE_CPP
#include "globals.cpp"
#include "clickhandlers.cpp"
#include "main.cpp"

void dialogueBox(string name)
{
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
}

void showInstructions(int gameLevel, int page)
{
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

	assetName += page;

	//and display it
	overlays.push_back(framework.createSprite(assetName, 0, 0, 600, 600));

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

#endif