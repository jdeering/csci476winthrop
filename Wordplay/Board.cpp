class Board
{
	public:
		//construct 
		Board(int);


		//dealing with the selected word	
		bool isWord();

		//submit the current word
		void submitWord();
		
		
	private:
		//user-selected level for the game
		int gameLevel;

		//keeps track of the letter tiles based on their position
		Tile boardset[9][9];

		//keep a vector of the tiles for the current word
		vector <Tile> currentWord;
};


#include <string>

#include "Board.h"


Board::Board(int lvl)
{
	//set the game level according to user input
	gameLevel = level;

	//generate the gameboard

	//display the gameboard
}

void Board::generateBoard()
{

}

void Board::displayBoard()
{

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
				if ((boardset[x+1][y+1].isSelected() && currentWord.at(currentWord.length) == boardset[x+1][y+1]) ||
					(boardset[x-1][y-1].isSelected() && currentWord.at(currentWord.length) == boardset[x-1][y-1]) ||
					(boardset[x+1][y].isSelected() && currentWord.at(currentWord.length) == boardset[x+1][y]) ||
					(boardset[x-1][y].isSelected() && currentWord.at(currentWord.length) == boardset[x-1][y]) ||
					(boardset[x][y+1].isSelected() && currentWord.at(currentWord.length) == boardset[x][y+1]) ||
					(boardset[x][y-1].isSelected() && currentWord.at(currentWord.length) == boardset[x][y-1]) ||
					(boardset[x+1][y-1].isSelected() && currentWord.at(currentWord.length) == boardset[x+1][y-1]) ||
					(boardset[x-1][y+1].isSelected() && currentWord.at(currentWord.length) == boardset[x-1][y+1]) 
					)
				{
					validMove = true;
				}

				break;

			//for levels three and four
			case 3:
			case 4:
				//allow for any tile in cardinal direction
				if ((boardset[x+1][y].isSelected() && currentWord.at(currentWord.length) == boardset[x+1][y]) ||
					(boardset[x-1][y].isSelected() && currentWord.at(currentWord.length) == boardset[x-1][y]) ||
					(boardset[x][y+1].isSelected() && currentWord.at(currentWord.length) == boardset[x][y+1]) ||
					(boardset[x][y-1].isSelected() && currentWord.at(currentWord.length) == boardset[x][y-1]) 
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

void Board::addLetter(Tile lastLetter)
{
	//add the letter to the back of our current word
	currentWord.push_back(boardset[x][y]);
	
	//change the word's appearance to indicate whether it's a submittable word or not
	changeAppearance();
}

void Board::removeLetter(Tile toRemove)
{
	//unselect the top letter
	currentWord.top().unhighlight();

	//recursively remove the letters in the word until we reach the letter the user clicked on 
	if (currentWord.pop() != toRemove)
	{		
		//go with the next title
		removeLetter(toRemove);
	}
	//if we've found it, remove & stop recursing
	else{
		currentWord.pop();

		//change our word's appearance to reflect its valididty
		changeAppearance();
	}
}

void Board::changeAppearance()
{
	//if it's a word, highlight it as valid
	if (isWord())
	{
		for (int i = 0; i < currentWord.length(); ++i)
			currentWord.at(i).highlightValid();
	}
	//otherwise highlight it as not valid
	else
	{
		for (int i = 0; i < currentWord.length(); ++i)
			currentWord.at(i).highlightInvalid();
	}
}

string Board::returnWord()
{
	string currentString = "";

	//go through the vector of tiles, putting all the letters into a string
	for (int i = 0; i < currentWord.length(); ++i){
		currentString += currentWord.at(i).getLetter();
	}

	//return the resultant string
	return currentString;
}

bool Board::isWord()
{
	
}

int Board::submitWord(){

	int wordScore;

	//check to make sure the word is valid
	if (isWord())
	{
		//score the word before we get rid of it
		//scoring is dependent on level
		wordScore = returnWord().length() * gameLevel * 10;

		//now, delete all those tiles and, dependent on level, replace appropriately
		switch (gameLevel)
		{

		//for levels one, two, and three, the tiles "fall" into place
		case 1:
		case 2:
		case 3:


			break;

		//for level four, the tiles are simply replaced with new tiles that are generated
		case 4:

			break;
		}

	}

	//if it's not, ignore it, you'll return 0

	//return the score for the word
	return wordScore;
}