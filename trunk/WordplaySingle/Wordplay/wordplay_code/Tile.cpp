/*
Lauren Cairco
26 February 2009
CSCI 476 Project

Tile.cpp

This file is implementation of Tile.h, the Tile class for use in the Wordplay game module.
Functions are described in the .h file. Cppdocs comments are also found in this file.

*/
#include "Tile.h"
#include <iostream>


//////////////////////////////
// constructors & utilities	//
//////////////////////////////

//default constructor
/*********************************************
	Default constructor for a Tile object. Uses <code>generateLetter</code> to decide which letter the tile should represent,
	sets the <code>letter</code> attribute to that letter, creates a <code>GFSprite</code> for the letter, and assigns it to
	the <code>relatedSprite</code> attribute. Also, sets the <code>selected</code> flag to show that the tile is not yet selected.
*********************************************/
Tile::Tile()
{
	//generate a tile based on letter distribution
	letter = generateLetter();

	//get the correct sprite based on the letter we just generated
	std::string assetName = "";
	assetName = "letter_";
	assetName = assetName + letter;
	relatedSprite = &GameFramework::createSprite(assetName,0,0,50,50);

	//the letter is not yet selected
	selected = 0;
}

//returns a letter that's been generated based on the probability of distribution
//of letters in the English language
/*********************************************
	Returns a randomly selected letter based on the probability of letter occurence found at http://www.csm.astate.edu/~rossa/datasec/frequency.html.

	@return a letter
*********************************************/
char Tile::generateLetter(){
	//generate random number between 0 and 100 (double precision)
	int leftDecimal = (rand() % 100);
	double rightDecimal = (rand() % 1000) / 1000.00;
	double n = leftDecimal + rightDecimal;	

	//depending on where it is in the distribution, return a letter
	//distribution based on http://www.csm.astate.edu/~rossa/datasec/frequency.html
	if (n < 8.167) return 'a';
	else if (n < 9.659) return 'b';
	else if (n < 12.441) return 'c';
	else if (n < 16.694) return 'd';
	else if (n < 29.396) return 'e';
	else if (n < 31.624) return 'f';
	else if (n < 33.639) return 'g';
	else if (n < 39.733) return 'h';
	else if (n < 46.729) return 'i';
	else if (n < 46.882) return 'j';
	else if (n < 47.654) return 'k';
	else if (n < 51.679) return 'l';
	else if (n < 54.085) return 'm';
	else if (n < 60.834) return 'n';
	else if (n < 68.341) return 'o';
	else if (n < 70.27) return 'p';
	else if (n < 70.365) return 'q';
	else if (n < 76.352) return 'r';
	else if (n < 82.679) return 's';
	else if (n < 91.735) return 't';
	else if (n < 94.493) return 'u';
	else if (n < 95.471) return 'v';
	else if (n < 97.831) return 'w';
	else if (n < 97.981) return 'x';
	else if (n < 99.955) return 'y';
	else return 'z';
}

//////////////////////////////////
//		attribute returning		//
//////////////////////////////////

//returns the letter the tile represents
/*********************************************
	Returns the <code>letter</code> attribute of the object.

	@return value of <code>letter</code> attribute
*********************************************/
char Tile::getLetter()
{
	return letter;
}

//returns whether the tile is selected or not
/*********************************************
	Returns the <code>selected</code> attribute of the object. 0 is not selected, 1 is selected
	as part of an invalid word, and 2 is selected as part of a valid word. This also corresponds
	to the frame number of the <code>GFSprite</code> that should be displayed for this object.

	@return value of <code>selected</code> attribute
*********************************************/
int Tile::isSelected()
{
	return selected;
}

//returns pointer to the related sprite
/*********************************************
	Returns a pointer to the <code>relatedSprite</code> attribute of the object.

	@return a pointer to the <code>relatedSprite</code> attribute of the object
*********************************************/
GFSprite * Tile::returnSprite(){
	return relatedSprite;
}

//////////////////////////////////
//		display functions		//
//////////////////////////////////

//places the tile at the given xy coordinates
//used to show the tile initially
/*********************************************
	Positions the <code>relatedSprite</code> of the object at (<code>x</code>, <code>y</code>) using the
	<code>GFSprite::setSpritePosition</code> function, and sets it visible using the <code>GFSprite::setVisible</code>
	function.

	@param x desired x position for sprite
	@param y desired y position for sprite
*********************************************/
void Tile::showTile(int x, int y)
{
	relatedSprite->setSpritePosition(x,y);
	relatedSprite->setVisible(true);
	//show the letter as unselected
	unhighlight();
}

//this is used to slide a tile down
/*********************************************
	Makes the sprite associated with the object slide down 50 pixels * <code>spacesToDrop</code>. This is used
	in gameplay when replacing letter tiles with the tiles above them. Uses the <code>GFSprite::MoveTo</code> function.

	@param spacesToDrop number of tiles the sprite should move down
*********************************************/
void Tile::dropDown(int spacesToDrop)
{
	relatedSprite->moveTo(relatedSprite->_x, relatedSprite->_y + (50 * spacesToDrop), 20);
}

/*********************************************
	Makes the sprite associated with the object slide down from the top of the screen at (<code>x</code> * 50 + 25, 0) to (<code>x</code> * 50 + 25, <code>y</code> * 50 + 25).
	The coefficients and additons are used because of the position of the gameboard in the game play-- <code>x</code> and <code>y</code> are referring to the indices of the
	row and column we want this sprite to show up at on the gameboard.

	Uses the <code>showTile</code> function to get it in the appropriate starting place, and <code>GFSprite::moveTo</code> to get it to the right place.
	@param x x index of where tile should end up on the gameboard
	@param y y index of where the tile should end up on the gameboard
*********************************************/
//this is used to slide a tile from the top of the screen
//to the specified spot x-column and y-row
void Tile::slideFromTop(int x, int y)
{
	showTile(x * 50 + 25, 0);
	//slide to position we want
	relatedSprite->moveTo(x * 50 + 25, y * 50 + 25, 20);

}

//show the tile as highlighted and as part of a valid word
/*********************************************
	Changes the frame of <code>relatedSprite</code> to frame 2 using <code>GFSprite::setSpriteFrame</code>, and the <code>selected</code>
	attribute to 2, to denote that the <code>Tile</code> has been selected as part of a valid word
*********************************************/
void Tile::highlightValid()
{
	selected = 2;
	relatedSprite->setSpriteFrame(2);
}

//show the tile as highlighted and not a part of a valid word
/*********************************************
	Changes the frame of <code>relatedSprite</code> to frame 1 using <code>GFSprite::setSpriteFrame</code>, and the <code>selected</code>
	attribute to 1, to denote that the <code>Tile</code> has been selected as part of an invalid word
*********************************************/
void Tile::highlightInvalid()
{
	selected = 1;
	relatedSprite->setSpriteFrame(1);
}

//show the tile as unselected
/*********************************************
	Changes the frame of <code>relatedSprite</code> to frame 0 using <code>GFSprite::setSpriteFrame</code>, and the <code>selected</code>
	attribute to 0, to denote that the <code>Tile</code> is not selected
*********************************************/
void Tile::unhighlight()
{
	selected = 0;
	relatedSprite->setSpriteFrame(0);
}