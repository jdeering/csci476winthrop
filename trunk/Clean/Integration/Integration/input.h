/*
Jason Deering

input.h

Contains the Mouse and Keyboard classes to handle input.

The Mouse class controls the state changes of the left and right mouse button.
The Keyboard class controls the state changes of all keyboard keys.

Mouse
	DATA ITEMS	
		int x - the current x position of the mouse on screen
		int y - the current y position of the mouse on screen
		bool leftPressed - the current pressed state of the left mouse button
		bool rightPressed - the current pressed state of the right mouse button
		BoundingBox pointer - a collidable BoundingBox to test collision with sprites

	FUNCTIONS
		void Update(int x, int y) - updates the x and y variables each tick to the current mouse position given by Allegro
		bool StateChange(int button, int state, int x, int y) - returns true if the state of the mouse has changed
				all parameters are by reference, so the button the state changed on, the new state, and the mouse's (x,y) position
				are returned through the parameters
		BoundingBox GetPointer() - returns the pointer BoundingBox reference
		bool LeftClick(BoundingBox &box) - returns true if the left mouse button was clicked on top of the parameter BoundingBox
		bool RightClick(BoundingBox &box) - returns true if the right mouse button was clicked on top of the parameter BoundingBox
		bool LeftRelease(BoundingBox &box) - returns true if the left mouse button was released on top of the parameter BoundingBox
		bool RightRelease(BoundingBox &box) - returns true if the right mouse button was released on top of the parameter BoundingBox
	
Keyboard
	DATA ITEMS	
		int pressed[KEY_MAX] - array of all keyboard key states (pressed or not pressed)
	FUNCTIONS
		bool StateChange(int &key, int &state) - returns true if a key's state has changed, the key and the new state are returned
													through the parameters
*/


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