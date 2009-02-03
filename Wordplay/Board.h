#include <string>
#include <vector>#include "Tile.h"

class Board
{
	public:
		//construct 
		Board(int);

		//handle clicks
		void clickHandler(int, int);
		
		//dealing with the selected word
		string returnWord();		
		bool isWord();
		void addLetter();
		void removeLetter();

		//visually change the word when it is submittable
		void showValid();

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
