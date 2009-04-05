/*
Jason Deering

collidable.h

This class is for use in the Framework.

The BoundingBox class is used for collision detection of objects on the screen.

DATA ITEMS
	int width - current pixel width of the BoundingBox
	int height - current pixel height of the BoundingBox
	int x - current x position of the BoundingBox
	int y - current y position of the BoundingBox

FUNCTIONS
	bool isColliding(const BoundingBox&) - returns true if this BoundingBox is colliding with the specified other BoundingBox
	void SetPosition(int x, int y) - sets the position of the BoundingBox to (x,y)
	void SetSize(int w, int h) - sets the pixel size of the BoundingBox to w x h
	int GetPositionX() - returns the current x position of the BoundingBox
	int GetPositionY() - returns the current y position of the BoundingBox
	int GetWidth() - returns the current pixel width of the BoundingBox
	int GetHeight() - returns the current pixel height of the BoundingBox

*/

#ifndef _COLLIDABLE_H
#define _COLLIDABLE_H

class BoundingBox
{
private:
	int width, height;
	int x, y;
public:
	// Default Constructor
	BoundingBox(){ width = 0; height = 0; x = 0; y = 0; }
	BoundingBox(int, int, int, int);
	BoundingBox(const BoundingBox&);
	~BoundingBox();
	bool isColliding(const BoundingBox&);
	void SetPosition(int, int);
	void SetSize(int, int);
	int GetPositionX();
	int GetPositionY();
	int GetWidth();
	int GetHeight();
};


#endif