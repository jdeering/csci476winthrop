#include "Board.h"

Board::Board(int lvl)
{
	//set the game level according to user input
	gameLevel = lvl;

	//generate the gameboard
	generateBoard();

	//display the gameboard
	displayBoard();
}

void Board::generateBoard()
{
	
	//i don't think I need this any more
	/*
	//for each position in the array, make a new tile
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			//check for compiling...
			Tile * nT;
			nT = new Tile();
			boardset[i][j] = nT;
		}
			
	}
	 
	 */

}

void Board::displayBoard()
{
	//display each tile in the array in its appropriate position
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			boardset[i][j].showTile( (25 + 50 * i), (25 + 50 * j) );
		}
	}
}

void Board::clickHandler(int x, int y)
{
	//we're looking for the array subscripts of the tile the user clicked on

	bool found = false;
	
	//subtract 25 from x and y to make math easier, this accounts for the top and left margins of the board
	x = x - 25;
	y = y - 25;

	//figure out where we are x-wise
	for (int i = 0; i < 450 && !found; i = i + 50)
	{
		//once we find it, divide our i-value by 50, that'll give us our subscript
		if (x > i && x < (i + 50))
		{
			x = i / 50;
			found = true;
		}
	}

	found = false;
	//and figure out where we are y-wise in the same manner
	for (int i = 0; i < 450 & ! found; i = i + 50)
	{
		if (x > i && x < (i + 50))
		{
			y = i / 50;
			found = true;
		}
	}

	//now that we have our x and y positions, we start dealing with the tile that's in that array subscript
	//first, if it's selected, we need to deselect it and any letters that follow it in the word
	if (boardset[x][y].isSelected())
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
				if ((boardset[x+1][y+1].isSelected() && currentWord.at(currentWord.size() - 1).tileObj == &boardset[x+1][y+1]) ||
					(boardset[x-1][y-1].isSelected() && currentWord.at(currentWord.size() - 1).tileObj == &boardset[x-1][y-1]) ||
					(boardset[x+1][y].isSelected() && currentWord.at(currentWord.size() - 1).tileObj == &boardset[x+1][y]) ||
					(boardset[x-1][y].isSelected() && currentWord.at(currentWord.size() - 1).tileObj == &boardset[x-1][y]) ||
					(boardset[x][y+1].isSelected() && currentWord.at(currentWord.size() - 1).tileObj == &boardset[x][y+1]) ||
					(boardset[x][y-1].isSelected() && currentWord.at(currentWord.size() - 1).tileObj == &boardset[x][y-1]) ||
					(boardset[x+1][y-1].isSelected() && currentWord.at(currentWord.size() - 1).tileObj == &boardset[x+1][y-1]) ||
					(boardset[x-1][y+1].isSelected() && currentWord.at(currentWord.size() - 1).tileObj == &boardset[x-1][y+1]) 
					)
				{
					validMove = true;
				}

				break;

			//for levels three and four
			case 3:
			case 4:
				//allow for any tile in cardinal direction
				if ((boardset[x+1][y].isSelected() && currentWord.at(currentWord.size() - 1).tileObj == &boardset[x+1][y]) ||
					(boardset[x-1][y].isSelected() && currentWord.at(currentWord.size() - 1).tileObj == &boardset[x-1][y]) ||
					(boardset[x][y+1].isSelected() && currentWord.at(currentWord.size() - 1).tileObj == &boardset[x][y+1]) ||
					(boardset[x][y-1].isSelected() && currentWord.at(currentWord.size() - 1).tileObj == &boardset[x][y-1]) 
					)
				{
					validMove = true;
				}
				break;
		}

		//if we've decided it's a valid move
		if (validMove){
			//add the letter to the word
			addLetter(boardset[x][y], x, y);
		}

		//otherwise ignore the click
	}

}

void Board::addLetter(Tile lastLetter, int arrayX, int arrayY)
{
	TileItem newTile;
	newTile.tileObj = &lastLetter;
	newTile.x = arrayX;
	newTile.y = arrayY;
	
	//add the letter to the back of our current word
	currentWord.push_back(newTile);
	
	//change the word's appearance to indicate whether it's a submittable word or not
	changeAppearance();
}

void Board::removeLetter(Tile toRemove)
{
	//unselect the top letter
	currentWord.at(currentWord.size() - 1).tileObj->unhighlight();

	//recursively remove the letters in the word until we reach the letter the user clicked on 
	if (currentWord.back().tileObj != &toRemove)
	{		
		currentWord.pop_back();

		//go with the next tile
		removeLetter(toRemove);
	}
	//if we've found it, remove & stop recursing
	else{
		currentWord.pop_back();

		//change our word's appearance to reflect its valididty
		changeAppearance();
	}
}

void Board::changeAppearance()
{
	//if it's a word, highlight it as valid
	if (isWord())
	{
		for (int i = 0; i < currentWord.size(); ++i)
			currentWord.at(i).tileObj->highlightValid();
	}
	//otherwise highlight it as not valid
	else
	{
		for (int i = 0; i < currentWord.size(); ++i)
			currentWord.at(i).tileObj->highlightInvalid();
	}
}

std::string Board::returnWord()
{
	std::string currentString = "";

	//go through the vector of tiles, putting all the letters into a string
	for (int i = 0; i < currentWord.size(); ++i){
		currentString += currentWord.at(i).tileObj->getLetter();
	}

	//return the resultant string
	return currentString;
}

void Board::checkWord(Dictionary d)
{
	validWord = d.search(returnWord());
}

int Board::submitWord(){

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

bool Board::isWord()
{
	return validWord;
}

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
				//delete the letter from the board
				boardset[currentWord.back().x][currentWord.back().y].delete();
				
				//fill in from top
				if (currentWord.back().y > 0)
				{
					//drop blocks down until the only blank one remaining is at top
					for (int i = 0; i < currentWord.back().y; i++){
						boardset[currentWord.back().x][currentWord.back().y + i] = boardset[currentWord.back().x][currentWord.back().y + 1];
						boardset[currentWord.back().x][currentWord.back().y + 1].dropDown();
						
						currentWord.pop_back();
					}
				}
				Tile * nT;
				nT = new Tile();
			
				nt->slideFromTop();
				
				//fill in the top block with a new letter
				boardset[currentWord.back().x][0] = nT;
			}
			
			break;
			
			//for level four, the tiles are simply replaced with new tiles that are generated
		case 4:
			while (currentWord.size()){
				Tile * nT;
				nT = new Tile();
				boardset[currentWord.back().x][currentWord.back().y] = nT;
			}
		break;
	}
}