#ifndef TILE_H
#define TILE_H
#include <string>
#include "../APIFramework/GameFramework.h"

class Tile
{
	public:
		Tile();
		char getLetter();
		void toggleImage();
		void showTile(int, int);
		bool isSelected();
		void highlightValid();
		void highlightInvalid();
		void unhighlight();

		void dropDown(int, int);
		void slideFromTop(int, int);
		Tile & operator=(Tile & rhs);
	
		
		GFSprite * relatedSprite;

	private:
		char letter;
		bool selected;
		char generateLetter();
};
#endif
