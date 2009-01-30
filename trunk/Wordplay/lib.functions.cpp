#include <string>

#include "Tile.h"

int scoreWord(std::string str, int lvl)
{
	//arbitrary scoring algorithm:
	//give one point for every letter in the string, and multiply by 10, 20, 30, or 40
	//depending on what level the user is on
	return str.length() * lvl * 10;
}

//////////////////////////////////////////
//	beginning the game					//
//////////////////////////////////////////

void showSetLevelDialogue()
{
	//show the user a choice of levels with explanations of the rules

	//display background dialog box, it blocks out the whole gameplay area

	//display the four buttons for each of the levels

	//display the four text labels below them, and the level descriptions

	//need to think about how to make level descriptions concise and understandable
	

}

void hideSetLevelDialogue(){
	//when the user clicks a level, we want to take away the dialogue box

	//and begin the rest of gameplay

	//show instruction screen
}


void setLevel(int level)
{
	//this game offers four levels

	//for level one
	if (level == 1)
	{

	}
	
	//for level two
	else if (level == 2)
	{

	}

	//for level three
	else if (level == 3)
	{

	}

	//for level four
	else
	{

	}

}

void showInstructions(int level){
	//dependent on level, show text and picture instructions for the game

	//place a button that lets the user begin the game
}

void hideInstructions(){

	//hide the instruction screen

}

//////////////////////////////////////////
//	gameplay setup			//
//////////////////////////////////////////

void setupGame()
{

	//set up board

	//set up dictionary

	//set up layout of everything on screen

}

//////////////////////////////////////////
//	click functions			//
//////////////////////////////////////////

void clickHandler(int x, int y)
{

	//figure out where we've clicked and send it to an appropriate handler
	//the clickable items will depend on where we are in gameplay

	//during choosing a level
	if()
	{
		//if it's a level button
		if()
		{
			//hide the dialogue box
			hideSetLevelDialogue()
			//decide which level it is, and select that level
			setLevel(n);
			//go ahead and show instructions for that level
			showInstructions(level);
		}

	}
			
	//during instructions
	else if ()
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
	else if ()
	{
	
		//if it's a letter
		if()
		{
			//select it or unselect it

			//check to see if the word's valid
			//if it is
			if()
			{
				//highlight the button
			}

			//otherwise
			else
			{
				//make sure the button is not highlighted
			}
		

		}

		//if it's the submit word button
		else if()
		{

			//check to see if the word is valid

			//if it is
			if()
			{
				//submit the word
			}
	
			//otherwise ignore it, we don't need to submit the word
		}
		
		//if it's the reset board button
		else if()
		{

		}

		//if it's the end game button
		else if ()
		{

		}

	}
}

void clickLetter(Tile t)
{

	//a bunch of this will probably go in the board class but I'm going to go ahead and pseudocode it out

	
	//find the letter that the user just clicked on

	//if the letter is not currently selected

		//if the letter is adjacent to the most recently selected tile

			//highlight it

			//add it to the back of the current word we're forming

			//check to see if that word is in the dictionary

			//if the word is in the dictionary, highlight the button that lets the user submit the word
			
			//if not, we take no action

	//if the letter is currently selected

		//unhighlight it

		//if it's the last letter

			//take it off the end of the current word
		
		//if it's not the last letter

			//take off the letters before the letter we clicked on and start it there

	//update the currrent word in the game interface

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
