/*
Lauren Cairco
26 February 2009
CSCI 476 Project

Board.cpp

This class is for use with the Wordplay game module. It's the implementation for Board.h.
All the function details are found here.

*/

#include "Board.h"

//////////////////////////////
//	construction & display	//
//////////////////////////////

//accepts and sets game level and pointer to the dictionary to be used to check words
Board::Board(int lvl, Dictionary * d)
{	
	gameLevel = lvl;
	userDictionary = d;
}

//displays the board
void Board::displayBoard()
{
	//display each tile in the array in its appropriate position
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			boardset[i][j].tileObj->showTile( (25 + 50 * i), (25 + 50 * j) );
		}
	}
}

//////////////////////////////////
//	actions on individual tiles	//
//////////////////////////////////

//handles all the clicks within the board area
void Board::clickHandler(int x, int y)
{
	//figure out which tile object the user clicked on
	x = x - 25;
	x = int((x - (x % 50)) / 50);
	y = y - 25;
	y = int((y - (y % 50)) / 50);

	//now that we have our x and y positions, we start dealing with the tile that's in that array subscript
	//first, if it's selected, we need to deselect it and any letters that follow it in the word
	if (boardset[x][y].tileObj->isSelected())
	{
		removeLetter(boardset[x][y]);
	}
	//if it's not selected
	else
	{
		bool validMove = false;

		//check to see if it's a valid move
		//this is level dependent
		switch(gameLevel)
		{
			//for levels one and two
			case 1:
			case 2:
				//allow for any neighboring tile (cardinal directions as well as diagonals)
				//check to make sure it is selected, and it is the end of the word
				if ((boardset[x+1][y+1].tileObj->isSelected() && currentWord.at(currentWord.size() - 1) == &boardset[x+1][y+1]) ||
					(boardset[x-1][y-1].tileObj->isSelected() && currentWord.at(currentWord.size() - 1) == &boardset[x-1][y-1]) ||
					(boardset[x+1][y].tileObj->isSelected() && currentWord.at(currentWord.size() - 1) == &boardset[x+1][y]) ||
					(boardset[x-1][y].tileObj->isSelected() && currentWord.at(currentWord.size() - 1) == &boardset[x-1][y]) ||
					(boardset[x][y+1].tileObj->isSelected() && currentWord.at(currentWord.size() - 1) == &boardset[x][y+1]) ||
					(boardset[x][y-1].tileObj->isSelected() && currentWord.at(currentWord.size() - 1) == &boardset[x][y-1]) ||
					(boardset[x+1][y-1].tileObj->isSelected() && currentWord.at(currentWord.size() - 1) == &boardset[x+1][y-1]) ||
					(boardset[x-1][y+1].tileObj->isSelected() && currentWord.at(currentWord.size() - 1) == &boardset[x-1][y+1]) 
					)
				{
					validMove = true;
				}

				break;

			//for levels three and four
			case 3:
			case 4:
				//allow for any tile in cardinal direction
				if ((boardset[x+1][y].tileObj->isSelected() && currentWord.at(currentWord.size() - 1) == &boardset[x+1][y]) ||
					(boardset[x-1][y].tileObj->isSelected() && currentWord.at(currentWord.size() - 1) == &boardset[x-1][y]) ||
					(boardset[x][y+1].tileObj->isSelected() && currentWord.at(currentWord.size() - 1) == &boardset[x][y+1]) ||
					(boardset[x][y-1].tileObj->isSelected() && currentWord.at(currentWord.size() - 1) == &boardset[x][y-1]) 
					)
				{
					validMove = true;
				}
				break;
		}

		//if we've decided it's a valid move
		if (validMove){
			//add the letter to the word
			addLetter(boardset[x][y]);
		}

		//otherwise ignore the click
	}
}

//add the letter passed in to the current word
void Board::addLetter(TileItem &t)
{
	currentWord.push_back(&t);
	//change the word's appearance to indicate whether it's a submittable word or not
	checkWord();
	changeAppearance();
}

//remove the letter passed in from the word, and any letters following it
//works recursively
void Board::removeLetter(TileItem & toRemove)
{
	//unselect the top letter
	currentWord.at(currentWord.size() - 1)->tileObj->unhighlight();

	//recursively remove the letters in the word until we reach the letter the user clicked on 
	if (currentWord.back()->tileObj != toRemove.tileObj)
	{		
		currentWord.pop_back();

		//go with the next tile
		removeLetter(toRemove);
	}
	//if we've found it, remove & stop recursing
	else{
		currentWord.pop_back();

		//change our word's appearance to reflect its valididty
		checkWord();
		changeAppearance();
	}
}

//////////////////////////////////////
//	dealing with the selected word	//
//////////////////////////////////////

//change the appearance of the word on the basis of whether it's valid or not
void Board::changeAppearance()
{
	//if it's a word, highlight it as valid
	if (isWord())
	{
		for (int i = 0; i < (signed)currentWord.size(); ++i)
			currentWord.at(i)->tileObj->highlightValid();
	}
	//otherwise highlight it as not valid
	else
	{
		for (int i = 0; i < (signed)currentWord.size(); ++i)
			currentWord.at(i)->tileObj->highlightInvalid();
	}
}

//checks the current word against the dictionary and submits if it's valid
//returns 10 * wordlength * levelnumber for the score
int Board::submitWord()
{
	int wordScore = 0;

	//check to make sure the word is valid
	if (isWord())
	{
		//score the word before we get rid of it
		//scoring is dependent on level
		wordScore = returnWord().length() * gameLevel * 10;

		//remove & replace the letters we just used
		replaceLetters();
	}

	//if it's not, ignore it, you'll return 0

	//return the score for the word
	return wordScore;
}


//replaces the letters that are in the current word with new letters, method depends on level
//should be called when the word is submitted
void Board::replaceLetters()
{
	//now, delete all those tiles and, dependent on level, replace appropriately
	switch (gameLevel)
	{
			
			//for levels one, two, and three, the tiles "fall" into place
		case 1:
		case 2:
		case 3:
			while (currentWord.size())
			{
				
				//fill in from top
				if (currentWord.back()->y > 0)
				{
					//drop blocks down until the only blank one remaining is at top
					for (int i = 0; i < currentWord.back()->y; i++){
						boardset[currentWord.back()->x][currentWord.back()->y + i] = boardset[currentWord.back()->x][currentWord.back()->y + 1];
						boardset[currentWord.back()->x][currentWord.back()->y + 1].tileObj->dropDown();
					}
				}
				Tile * nT;
				nT = new Tile();
			
				nT->slideFromTop((currentWord.back()->x) * 50 + 25, (currentWord.back()->y) * 50 + 25);
				
				//fill in the top block with a new letter
				boardset[currentWord.back()->x][0].tileObj = nT;

				currentWord.pop_back();
			}
			
			break;
			
			//for level four, the tiles are simply replaced with new tiles that are generated
		case 4:
			while (currentWord.size()){
				Tile * nT;
				nT = new Tile();
				boardset[currentWord.back()->x][currentWord.back()->y].tileObj = nT;

				currentWord.pop_back();
			}
		break;
	}
}

//checks the word to see if it's in the dictionary or not
void Board::checkWord()
{
	validWord = userDictionary->search(returnWord());
}

//////////////////////////////
//	returning properties	//
//////////////////////////////

//returns whether the word is valid or not
bool Board::isWord()
{
	return validWord;
}

//returns the current word as a string
std::string Board::returnWord()
{
	std::string currentString = "";

	//go through the vector of tiles, putting all the letters into a string
	for (int i = 0; i < (signed)currentWord.size(); ++i){
		currentString += currentWord.at(i)->tileObj->getLetter();
	}

	//return the resultant string
	return currentString;
}

//returns the board level
int Board::returnLevel()
{
	return gameLevel;
}