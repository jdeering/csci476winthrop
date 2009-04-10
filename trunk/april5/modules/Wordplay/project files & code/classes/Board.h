/*
Lauren Cairco
26 February 2009
CSCI 476 Project

Board.h

This class is for use with the Wordplay game module.
It also requires the STL string and vector classes to deal with some internal stuff.
The class deals with the layout and click handling of the tiles on the gameboard. It keeps track of
highlighting the tiles when they need to be highlighted, of submitting words on user request, on keeping
track of whether the user word is in the dictionary or not. It also fills in the tiles that disappear because
the word is submitted.

TYPEDEF

struct TileItem
	holds a pointer to a Tile object (tileObj) and its x and y subscripts in the larger board array

DATA ITEMS

int gameLevel
	the level of the game that the user chose--passed in as a parameter into the class constructor
vector <TileItem*> currentWord
	holds pointers to the tiles that are in the currently formed word
Dictionary * userDictionary
	the dictionary to check the words against--passed in as a parameter into the class constructor
bool validWord
	holds whether the word is in the dictionary or not

FUNCTIONS
--Public functions:
Board(level, Dictionary*)
	given the game level and dictionary as parameters, sets up (but does not display) the 9x9 game board of tiles
displayBoard
	shows the board on the screen
bool isWord
	returns whether the word is valid or not (value of validWord)
int returnLevel
	returns the level of the game (value of gameLevel)
string returnWord
	returns the string of the word the user has been selecting
int submitWord
	submits the currently selected word, if it is a valid word; returns the word's score
clickHandler(x, y)
	given the x and y coordinates of the click, decides which letter has been clicked and handles it appropriately

--Private functions:
addLetter(TileItem&)
	adds the parameter TileItem to the vector of the current word
removeLetter(TileItem&)
	removes the tile that's passed in as a parameter, and any letters following it in the current word
changeAppearance
	changes the word's appearance to show whether it is an acceptable word or not
replaceLetters
	replaces all the letters on the gameboard that have been removed due to the current word being submitted
checkWord
	checks whether the word is in the dictionary or not, changing the value of validWord
*/

#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <vector>
#include "Dictionary.h"
#include "Tile.h"

class Board
{
	typedef struct {
		Tile * tileObj;
		int x;
		int y;
	} TileItem;

	public:
		Board(int, Dictionary *);		
		void displayBoard();
		
		bool isWord();
		int returnLevel();

		std::string returnWord();		
		int submitWord();
		
		void clickHandler(int, int);
		
	private:
		int gameLevel;

		TileItem boardset[9][9];
		std::vector<TileItem *> currentWord;
		Dictionary * userDictionary;
		bool validWord;

		void addLetter(TileItem &);
		void removeLetter(TileItem &);
		void checkWord();
		void changeAppearance();
	
		void replaceLetters();
};
#endif
