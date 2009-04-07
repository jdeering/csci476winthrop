/*
Lauren Cairco
26 February 2009
CSCI 476 Project

Tile.h

This class is for use with the Wordplay game module.
It requires the game framework header to be imported because it deals with everything to
do with the creation and display of the letter tiles on the game board.
It also requires the STL string class to deal with its sprite attributes

DATA ITEMS:
char letter
	contains the character letter of the character the tile represents
bool selected
	true if the letter is selected, false if it is not selected
GFSprite * relatedSprite
	holds a pointer to the sprite that is associated with this tile

FUNCTIONS:
Tile (constructor)
	Makes a new tile by generating a random letter, setting up the letter's sprite attributes,
	and setting the 'selected' attribute to false
char generateLetter
	returns a character based on the probability distribution of letters in the English language
	a private function, only used in the Tile constructor

char getLetter
	returns the letter the tile represents
bool isSelected
	returns whether the tile is selected or not
GFSprite * returnSprite
	returns the pointer to the related sprite

highlightValid
highlightInvalid
unhighlight
	changes the background color of the tile by changing the frame of its sprite

showTile(x,y)
	displays the tile with its top left corner at (x,y)
dropDown
	moves the tile down 50px from its location
slideFromTop(x,y)
	slides a tile down from the top of the screen to the specified coordinates

= overload
	allows for one tile to be assigned to another tile by copying over all its attributes

*/

#ifndef TILE_H
#define TILE_H
#include <string>
#include <ctime>
#include "../../../../api/GameFramework.h"

class Tile
{
	public:
		Tile();
		char getLetter();
		bool isSelected();
		GFSprite * returnSprite();

		void highlightValid();
		void highlightInvalid();
		void unhighlight();

		void showTile(int, int);
		void dropDown();
		void slideFromTop(int, int);

		Tile & operator=(Tile & rhs);	

	private:
		char letter;
		bool selected;
		GFSprite * relatedSprite;

		char generateLetter();
};
#endif
