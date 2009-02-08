#include "collidable.h"


/*******************************
	Default destructor
*******************************/
BoundingBox::~BoundingBox(){}

/*********************************************
	Constructor

	@param x The x coordinate of the top-left corner
	@param y The y coordinate of the top-left corner
	@param w The width of the box
	@param h The height of the box
*********************************************/
BoundingBox::BoundingBox(int x, int y, int w, int h)
{
	width = w;
	height = h;
	x = x;
	y = y;
}

/*********************************************
	Constructor

	@param box The <code>BoundingBox</code> being copied
*********************************************/
BoundingBox::BoundingBox(const BoundingBox &box)
{
	width = box.width;
	height = box.height;
	x = box.x;
	y = box.y;
}

/*********************************************
	Sets the x, y pixel coordinate position of the
	<code>BoundingBox</code>.

	@param x The x coordinate of the new position
	@param y The y coordinate of the new position
*********************************************/
void BoundingBox::SetPosition(int new_x, int new_y)
{
	x = new_x;
	y = new_y;
}

/*********************************************
	Sets the width and height of the
	<code>BoundingBox</code>.

	@param w The new width
	@param h The new height
*********************************************/
void BoundingBox::SetSize(int w, int h)
{
	width = w;
	height = h;
}

/*********************************************
	@return The current x coordinate of the
	<code>BoundingBox</code>'s position.
*********************************************/
int BoundingBox::GetPositionX()
{
	return x;
}


/*********************************************
	@return The current y coordinate of the
	<code>BoundingBox</code>'s position.
*********************************************/
int BoundingBox::GetPositionY()
{
	return y;
}


/*********************************************
	@return The current width of the
	<code>BoundingBox</code>.
*********************************************/
int BoundingBox::GetWidth()
{
	return width;
}


/*********************************************
	@return The current height of the
	<code>BoundingBox</code>.
*********************************************/
int BoundingBox::GetHeight()
{
	return height;
}

/*********************************************
	Determines whether or not
	the <code>BoundingBox</code> is overlapping 
	another <code>BoundingBox</code>

	@param other The <code>BoundingBox</code> being tested for overlap
	@return <code>true</code> if the BoundingBox is overlapping other, <code>false</code> otherwise
*********************************************/
bool BoundingBox::isColliding(const BoundingBox &other)
{
	int diffX, diffY;
	diffX = x - other.x;
	diffY = y - other.y;

	if(diffX <= (width + other.width) &&
		diffY <= (height + other.height))
		colliding = true;
	else
		colliding = false;

	return colliding;
}
