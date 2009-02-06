#include <string>
#include <vector>
#include "Dictionary.h"
#include "Tile.h"

class Board
{
	public:
		//construct 
		Board(int);

		//handle clicks
		void clickHandler(int, int);
		
		//dealing with the selected word
		std::string returnWord();		
		void checkWord(Dictionary);
		bool isWord();

		//submit the current word
		int submitWord();
		
		
		
	private:
		//user-selected level for the game
		int gameLevel;

		//keeps track of the letter tiles based on their position
		Tile boardset[9][9];

		//keep a vector of the tiles for the current word
		std::vector<Tile *> currentWord;

		bool validWord;

		void generateBoard();
		void displayBoard();

		void addLetter(Tile);
		void removeLetter(Tile);

		//visually change the word when it is submittable or unsubmittable
		void changeAppearance();

};
