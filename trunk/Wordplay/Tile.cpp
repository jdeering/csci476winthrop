#include "Tile.h"

Tile::Tile()
{
	//generate a tile based on letter distribution
	letter = generateLetter();

	//get the correct sprite based on the letter we just generated
	std::string assetName = letter + "_img";

	//could someone tell me what's wrong with this line of code?
	relatedSprite = GameFramework::createSprite(assetName,0,0,50,50);


	relatedSprite->setSpriteFrame(0);
	relatedSprite->setVisible(false);

	bool selected = false;
}

char Tile::getLetter()
{
	return letter;
}

void Tile::showTile(int x, int y)
{
	relatedSprite->setVisible(true);
	relatedSprite->setSpritePosition(x,y);

}

bool Tile::isSelected()
{
	return selected;
}

void Tile::highlightValid()
{
	relatedSprite->setSpriteFrame(1);
}

void Tile::highlightInvalid()
{
	relatedSprite->setSpriteFrame(2);
}

void Tile::unhighlight()
{
	relatedSprite->setSpriteFrame(0);
}

char Tile::generateLetter(){
	//generate random number between 0 and 100 (double precision)
	int leftDecimal = (rand() % 100);
	float rightDecimal = (rand() % 1000) / 1000.00;
	float n = leftDecimal + rightDecimal;	

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