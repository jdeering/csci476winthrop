#ifndef _COLLIDABLE_H
#define _COLLIDABLE_H

#include "allegro.h"

class BoundingBox
{
private:
	bool colliding;
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