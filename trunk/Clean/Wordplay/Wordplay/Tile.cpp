/*
Lauren Cairco
26 February 2009
CSCI 476 Project

Tile.cpp

This file is implementation of Tile.h, the Tile class for use in the Wordplay game module.
Functions are described in the .h file.

*/
#include "Tile.h"
#include <iostream>
using namespace std;

//////////////////////////////
// constructors & utilities	//
//////////////////////////////

//default constructor
Tile::Tile()
{
	//generate a tile based on letter distribution
	letter = generateLetter();
	//cout<<"letter: "<<letter<<endl;

	//get the correct sprite based on the letter we just generated
	std::string assetName = "";
	assetName = "letter_";
	assetName = assetName + letter;
	cout<<"assetName: "<<assetName<<endl;
	GameFramework gf = GameFramework::Instance();
	//relatedSprite = &gf.createSprite(assetName,0,0,50,50);

	//make the sprite invisible
	//relatedSprite->setVisible(false);
//	cout<<"set invisible"<<endl;
	//the letter is not yet selected
	bool selected = false;
}

//returns a letter that's been generated based on the probability of distribution
//of letters in the English language
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

//overload of = opreator allows us to assign one tile to another
Tile &Tile::operator= (Tile & rhs)
{
	letter = rhs.getLetter();
	selected = rhs.isSelected();
	relatedSprite = rhs.returnSprite();
	return *this;
}




//////////////////////////////////
//		attribute returning		//
//////////////////////////////////

//returns the letter the tile represents
char Tile::getLetter()
{
	return letter;
}

//returns whether the tile is selected or not
bool Tile::isSelected()
{
	return selected;
}

//returns pointer to the related sprite
GFSprite * Tile::returnSprite(){
	return relatedSprite;
}

//////////////////////////////////
//		display functions		//
//////////////////////////////////

//places the tile at the given xy coordinates
//used to show the tile initially
void Tile::showTile(int x, int y)
{
	cout<<"show at "<<x<<","<<y<<endl;
	relatedSprite->setSpritePosition(x,y);
	relatedSprite->setVisible(true);
	//show the letter as unselected
	relatedSprite->setSpriteFrame(0);

}

//this is used to slide a tile to the position just below it
//so we just move down in the y direction 50 px
void Tile::dropDown()
{
	//final parameter is how much time it should take moving there in milliseconds
	relatedSprite->moveTo(relatedSprite->_x, relatedSprite->_y + 50, 500);
}

//this is used to slide a tile from the top of the screen
//to the specified spot
void Tile::slideFromTop(int x, int y)
{
	showTile(x, 0);
	//slide to position we want
	relatedSprite->moveTo(x,y,500);

}

//show the tile as highlighted and as part of a valid word
void Tile::highlightValid()
{
	relatedSprite->setSpriteFrame(1);
}

//show the tile as highlighted and not a part of a valid word
void Tile::highlightInvalid()
{
	relatedSprite->setSpriteFrame(2);
}

//show the tile as unselected
void Tile::unhighlight()
{
	relatedSprite->setSpriteFrame(0);
}