#include <string>

#include "Tile.h"

int scoreWord(std::string str, int lvl)
{
	//arbitrary scoring algorithm:
	//give one point for every letter in the string, and multiply by 10, 20, 30, or 40
	//depending on what level the user is on
	return str.length() * lvl * 10;
}

void setupGame()
{

	//set up board

	//set up dictionary

	//set up layout of everything on screen

}

void clickHandler(int x, int y)
{

	//figure out where we've clicked and send it to an appropriate handler

	//if it's a letter

	//if it's the submit word button
	
	//if it's the reset board button

	//if it's the end game button

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
