#ifndef _INPUT_H
#define _INPUT_H

#include "globals.h"
#include "collidable.h"
#include "sprite.h"

class Mouse
{
private:
	int x, y;
	bool leftPressed, rightPressed;
	BoundingBox pointer;
public:
	Mouse();
	void Update(int &x_, int &y_);
	bool StateChange(int &button, int &state, int &x_, int &y_);
	BoundingBox GetPointer();
	bool LeftClick(BoundingBox &box);
	bool RightClick(BoundingBox &box);
	bool LeftRelease(BoundingBox &box);
	bool RightRelease(BoundingBox &box);
};

class Keyboard
{
private:
	int pressed[KEY_MAX];
public:
	Keyboard();
	bool StateChange(int &key, int &state);
};



#endif 