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
		//construct 
		Board(int, Dictionary *);

		//handle clicks
		void clickHandler(int, int);
		
		//dealing with the selected word
		std::string returnWord();		
		void checkWord(Dictionary);
		bool isWord();

		//submit the current word
		int submitWord();

		int returnLevel();

		void displayBoard();
		
		
		
	private:
		//user-selected level for the game
		int gameLevel;

		//keeps track of the letter tiles based on their position
		Tile boardset[9][9];

		//keep a vector of the tiles for the current word
		std::vector<TileItem> currentWord;

		Dictionary * userDictionary;

		bool validWord;

		void addLetter(Tile, int, int);
		void removeLetter(Tile);

		//visually change the word when it is submittable or unsubmittable
		void changeAppearance();
	
		void replaceLetters();
};
#endif
