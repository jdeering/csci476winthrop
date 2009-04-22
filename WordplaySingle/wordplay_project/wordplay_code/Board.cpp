/*
Lauren Cairco
26 February 2009
CSCI 476 Project

Board.cpp

This class is for use with the Wordplay game module. It's the implementation for Board.h.
All the function details are found here. Cppdocs comments are also found in this file.

*/

#include "Board.h"
#include <iostream>

//////////////////////////////
//	construction & display	//
//////////////////////////////

//accepts and sets game level and pointer to the dictionary to be used to check words
/*********************************************
	Default constructor for a Board object.

	@param lvl The gameplay level for the generated board. This determines what kinds of moves are legal and how words are scored.
	@param d A pointer to the Dictionary object that user-chosen words should be checked against.
*********************************************/
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
/*********************************************
	Displays an already-generated game board by calling the <code>slideFromTop</code> method for each <code>Tile</code>  contained in the <code>tileObj</code> array in the object.
*********************************************/
void Board::displayBoard()
{
	//display each tile in the array in its appropriate position
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			boardset[j][i].tileObj->slideFromTop(j, i);
		}
	}
}

/*********************************************
	Resets the entire gameboard, replacing each <code>Tile</code> held in the <code>TileItem</code>s in <code>boardset</code> with a new
	<code>Tile</code>. Then, it calls <code>displayBoard</code> so that the new letter values show up on the gameboard.
	The currentWord is also reset.

	@return the integer value of the gameplay level
*********************************************/
void Board::reset()
{
	//change out every tile object
	for (int m = 0; m < 9; ++m)
	{
		for (int n = 0; n < 9; ++n)
		{
			GameFramework::removeSprite(*boardset[m][n].tileObj->returnSprite());
			boardset[m][n].tileObj = new Tile();
		}
	}

	//clear out word
	while (currentWord.size() > 0)
	{
		currentWord.pop_back();
	}

	displayBoard();
}

//////////////////////////////////
//	actions on individual tiles	//
//////////////////////////////////

//handles all the clicks within the board area
/*********************************************
	Handles all the clicks within the gameboard area. Finds the tile that has been clicked, and, if it a valid move,
	calls addLetter to add it to the current word.

	@param x The x-coordinate of the click
	@param y The y-coordinate of the click
*********************************************/
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
/*********************************************
	Adds the <code>TileItem</code> passed in to the current word vector, then calls <code>checkWord</code> to see if it is a valid word
	and <code>changeAppearance</code> so that the word's appearance corresponds to its validity.

	@param t the <code>TileItem</code> that should be added to the curent word vector
*********************************************/
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
/*********************************************
	Removes the <code>TileItem</code> passed in, and any <code>TileItem</code>s with a larger subscript, from the <code>currentWord vector</code>. Unhighlights each letter it removes
	using the <code>unhighlight</code> method of the <code>Tile</code> class. After all the desired <code>TileItems</code> are removed, it calls <code>checkWord</code> to check the word against the dictionary
	and then <code>changeAppearance</code> so that the word's appearance corresponds to its validity. 

	@param toRemove the TileItem that should be removed from the current word. If there are any TileItems in the vector with a larger subscript then this TileItem, then they are also removed.
*********************************************/
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
/*********************************************
	Uses <code>isWord</code> to check if the current word is a valid word or not, then uses the <code>highlightValid</code> or <code>highlightInvalid</code>
	functions in the Tile class to make the <code>Tile</code>s' appearance correspond to the word's validity.

*********************************************/
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
/*********************************************
	Checks to see if the word is valid using <code>isWord</code>. If it's not a valid word, nothing happens.
	If it is a valid word, then it scores the word and returns the value, and calls <code>replaceLetters</code> so that
	the <code>TileItems<code> in the current word corresponding to the letters on the game board are replaced with new
	<code>TileItems</code> according to the replacement rules for each game level.

	@return the score for the word that's been submitted. A word is worth 10 * number of letters in the word * game level (1-4).
*********************************************/
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
/*********************************************
	Replaces all the letters that are in the <code>currentWord</code> vector, depending on the game level and their corresponding rules.
	For the first three levels, letters above the selected letters drop down to take the place of the discarded letters, and any unfilled
	letters at top are replaced with new <code>TileItems</code>. For the fourth level, new letters (and <code>TileItems</code> simply take
	the place of discarded letters, and surrounding letters do not move.
*********************************************/
void Board::replaceLetters()
{
	//now, delete all those tiles and, dependent on level, replace appropriately
	switch (gameLevel)
	{	
		//for levels one, two, and three, the tiles "fall" into place
		case 1:
		case 2:
		case 3:
			int spacesToDrop;

			for(int i = 0; i < 9; i++) // go through each column
			{
				spacesToDrop = 0; // reset spaces to drop for next row
				for(int j = 8; j >= 0; j--) // each row bottom to top
				{
					if(boardset[i][j].tileObj->isSelected())
					{
						// Remove it
						boardset[i][j].tileObj->unhighlight();
						GameFramework::removeSprite(*boardset[i][j].tileObj->returnSprite());
						spacesToDrop++; // add one to spacesToDrop
					}
					else // it's not selected, so drop it down spacesToDrop spaces
					{
						boardset[i][j + spacesToDrop] = boardset[i][j];
						boardset[i][j + spacesToDrop].y += spacesToDrop;
						boardset[i][j + spacesToDrop].tileObj->dropDown(spacesToDrop);
					}
				}
				// spacesToDrop now also refers to how many new tiles need to be dropped into the
				// current column, so drop that many tiles
				for(int k = spacesToDrop - 1; k >= 0; k--)
				{		
					Tile *nT = new Tile();
					boardset[i][k].tileObj = nT;
					//boardset[i][k].tileObj->showTile(i * 50 + 25, 25);
					boardset[i][k].tileObj->slideFromTop(i, k);
				}
			}

			currentWord.clear();			
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
/*********************************************
	Checks the current word represented in the <code>currentWord</code> vector against the dictionary, and sets <code>validWord</code>
	to true if the word is in the dictionary and meets the length constraints of each level, or false if it does not. For levels 1 and 2,
	words must be two letters long. For levels three and four, words must be three letters long.

	We use this function to set <code>validWord</code> to minimize the amount of dictionary searches we do.
*********************************************/
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
/*********************************************
	Returns whether the word is valid according to the <code>validWord</code> value.

	@return the value of <code>validWord</code>
*********************************************/
bool Board::isWord()
{
	return validWord;
}

//returns the current word as a std::string
/*********************************************
	Returns the string representation of the current word stored as a sequence of <code>TileItem</code>s in the <code>currentWord</code> vector.
	Uses the <code>getLetter</code> function of each <code>Tile</code> contained in each <code>TileItem</code> to get the letters represented by
	the <code>Tile</code>s and concatenates them into a string.


	@return the string representation of the word currently selected in gameplay
*********************************************/
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
/*********************************************
	Returns the integer value of the gameplay level. 1 is Easy, 2 is Medium, 3 is Difficult, and 4 is Challenge.

	@return the integer value of the gameplay level
*********************************************/
int Board::returnLevel()
{
	return gameLevel;
}

