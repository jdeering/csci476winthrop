#ifndef MAIN_CPP
#define MAIN_CPP

#include "../classes/Board.h"
#include "../classes/Tile.h"
#include "../classes/Dictionary.h"
#include "globals.cpp"
#include "clickhandlers.cpp"
#include "showhide.cpp"

//prototypes
void constructBoard(int level);
void makeDictionary();
void beginGame();
void exitGame();
void resetBoard();
void submitWord();

int main(){
	//display the beginning screen
	//GFSprite& createSprite(std::string, int, int, int, int);
	/////api
	overlays.push_back(framework.createSprite("intro", 0, 0, 600, 600));

	//set the correct click handler
	//	void mouseFunc(void (*f)(int, int, int, int));
	//***can't figure this out :(
		//mouseFunc((void *) masterClickHandler, 


	//and wait on the user to make their move!
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
	//display the background
	overlays.push_back(framework.createSprite("background", 0, 0, 600, 600));

	//display the gameboard
	gameBoard->displayBoard();

	//display the user score and current word text fields
	//GFText& createTextFromString(std::string, int, int, int);
	currentWord = &framework.createTextFromString("",35,535,40);
	gScore = &framework.createTextFromString("0", 490, 315, 20);

	//set the state of the game
	currentState = IN_GAME;
}

void exitGame()
{
	//send the score back to the framework
	/////api

	//end game
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
	//submit and score the word
	int wordScore;
	wordScore = gameBoard->submitWord();

	//add to the current score
	score = score + wordScore;

	//update the score and current word
	updateScore();
	updateCurrentWord();
}

#endif