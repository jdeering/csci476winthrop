/*
Lauren Cairco
26 February 2009
CSCI 476 Project

Board.cpp

This class is for use with the Wordplay game module. It's the implementation for Board.h.
All the function details are found here.

*/

#include "Board.h"
#include <iostream>

//////////////////////////////
//	construction & display	//
//////////////////////////////

//accepts and sets game level and pointer to the dictionary to be used to check words
Board::Board(int lvl, Dictionary * d)
{	
	gameLevel = lvl;
	userDictionary = d;

	for (int m = 0; m < 9; ++m)
	{
		for (int n = 0; n < 9; ++n)
		{
			boardset[m][n].x = m;
			boardset[m][n].y = n;
			boardset[m][n].tileObj = new Tile();
		}
	}
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
		if (currentWord.size() == 0){
			validMove = true;
		}
		else{
			switch(gameLevel)
			{
				//for levels one and two
				case 1:
				case 2:
					if((x > 0 && y > 0) && (&boardset[x-1][y-1] == (void *)currentWord.back()) ||
						(x > 0) && (&boardset[x-1][y] == (void *)currentWord.back()) ||
						(y > 0) && (&boardset[x][y-1] == (void *)currentWord.back()) ||
						(x < 8 && y > 0) && (&boardset[x+1][y-1] == (void *)currentWord.back()) ||
						(x < 8) && (&boardset[x+1][y] == (void *)currentWord.back()) ||
						(x > 0 && y < 8) && (&boardset[x-1][y+1] == (void *)currentWord.back()) ||
						(y < 8) && (&boardset[x][y+1] == (void *)currentWord.back()) ||
						(x < 8 && y < 8) && (&boardset[x+1][y+1] == (void *)currentWord.back())
						){
						validMove = true;
					}
					break;

				//for levels three and four
				case 3:
				case 4:
					//allow for any tile in cardinal direction
					if ((x > 0) && (&boardset[x-1][y] == (void *)currentWord.back()) ||
						(y > 0) && (&boardset[x][y-1] == (void *)currentWord.back()) ||
						(x < 8) && (&boardset[x+1][y] == (void *)currentWord.back()) ||
						(y < 8) && (&boardset[x][y+1] == (void *)currentWord.back())
						)
					{
						validMove = true;
					}
					break;
			}
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
void Board::addLetter(TileItem & t)
{
	currentWord.push_back(&t);

	//update the current word
	
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
			if (currentWord.at(i)->tileObj->isSelected() != 2){
				currentWord.at(i)->tileObj->highlightValid();
			}
	}
	//otherwise highlight it as not valid
	else
	{
		for (int i = 0; i < (signed)currentWord.size(); ++i)
			if (currentWord.at(i)->tileObj->isSelected() != 1) currentWord.at(i)->tileObj->highlightInvalid();
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

			//first, sort the word based on x-value
			sortWord();

			//now we have a sorted list with all the items in the same column grouped together
			//while there are still letters in the word
			while (currentWord.size())
			{
				vector <TileItem*> temp;

				bool finished = false;
				for (int i = 0; i < currentWord.size() && !finished; i++)
				{		
					//if we're done with this list we're finished
					if (currentWord.size == 1 || (currentWord.at(i) != currentWord.at(i + 1))
					{
						temp.push_back(*currentWord.at(i));
						finished = true;
					}
				}

				//so now we have a list of all the tiles that are in one column
				for (int i = 0; i < 

			}


		/*	while (currentWord.size())
			{
				//fill in from top
				if (currentWord.back()->y > 0)
				{
					//drop blocks down until the only blank one remaining is at top
					for (int i = 0; i < currentWord.back()->y; i++){
						boardset[currentWord.back()->x][i + 1] = boardset[currentWord.back()->x][i];
						boardset[currentWord.back()->x][i + 1].y += 1;
						boardset[currentWord.back()->x][i].tileObj->dropDown();
					}
				}
				Tile * nT;
				nT = new Tile();
			
				nT->slideFromTop((currentWord.back()->x) * 50 + 25, (currentWord.back()->y) * 50 + 25);
				
				//fill in the top block with a new letter
				boardset[currentWord.back()->x][0].tileObj = nT;

				currentWord.pop_back();
			}*/
			
			break;
			
			//for level four, the tiles are simply replaced with new tiles that are generated
		case 4:
			while (currentWord.size()){
				Tile * nT;
				nT = new Tile();
				GameFramework::removeSprite(*boardset[currentWord.back()->x][currentWord.back()->y].tileObj->returnSprite());
				boardset[currentWord.back()->x][currentWord.back()->y].tileObj = nT;
				boardset[currentWord.back()->x][currentWord.back()->y].tileObj->showTile(currentWord.back()->x * 50 + 25, currentWord.back()->y * 50 + 25);

				currentWord.pop_back();
			}
		break;
	}
}

//checks the word to see if it's in the dictionary or not
void Board::checkWord()
{
	//check for length requirements
	switch (gameLevel){
		case 1:
		case 2:
			if (returnWord().length() < 2) validWord = false;
			else validWord = userDictionary->search(returnWord());
		break;

		case 3:
		case 4:
			if (returnWord().length() < 3) validWord = false;
			else validWord = userDictionary->search(returnWord());
		break;
	}
}

//////////////////////////////
//	returning properties	//
//////////////////////////////

//returns whether the word is valid or not
bool Board::isWord()
{
	return validWord;
}

//returns the current word as a std::string
std::string Board::returnWord()
{
	std::string currentString = "";

	//go through the vector of tiles, putting all the letters into a std::string
	for (int i = 0; i < (signed)currentWord.size(); ++i){
		currentString += char(currentWord.at(i)->tileObj->getLetter() - 32);
	}

	//return the resultant std::string
	return currentString;
}

//returns the board level
int Board::returnLevel()
{
	return gameLevel;
}

void Board::sortWord(){
	//selection sort: inefficient, but I understand it!
	
	//sort according to y
	for (int i = 0; i < currentWord.size(); ++i){
		int greatest = i;
		for (int j = i + 1; j < currentWord.size(); ++j){
			if (currentWord.at(j)->x < currentWord.at(greatest)->x) greatest = j;
		}
		TileItem * t = currentWord.at(i);
		currentWord.at(i) = currentWord.at(greatest);
		currentWord.at(greatest) = t;
	}
}