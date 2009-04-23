/*
Jason Deering

sprite.h

This class is for use in the Framework.

The Sprite class controls the display of a single sprite.


DATA ITEMS	
	std::string fileRefName - the key reference to the file the sprite is associated with
	bool animating - whether or not the sprite is being animated
	bool loops - whether or not the sprite's animation loops back to the first frame
	bool visible - whether or not the sprite should be drawn
	bool alive - whether or not the sprite still exists
	int currFrame - the current frame in animation being displayed
	int numFrames - the number of frames in the animation
	int frameDelay - amount of time to delay in changing to the next frame of animation
	bool moving - whether or not the sprite is currently moving
	int rest - amount of frames to rest until the next time to move the sprite
	int new_x - x location to move to
	int new_y - y location to move to
	int speed - speed at which to move to the next location
	BoundingBox box

PRIVATE FUNCTIONS
	NextFrame() - changes to the next frame of animation
	MovePosition() - moves to the next position according to new_x, new_y, and speed

PUBLIC FUNCTIONS
	std::string GetSheetRef() - returns the reference to the sprite's associated bitmap
	bool isColliding(BoundingBox &box) - returns true if the sprite is colliding with the specified BoundingBox
	bool isColliding(Sprite &other_sprite) - returns true if the sprite is colliding with the specified Sprite
	bool isAnimating(void) - returns the current value of the data item animating
	bool isAlive(void) - returns the current value of the data item alive
	SetAlive(bool) - sets the value of alive to the value of the parameter
	SetVisible(int) - sets the value of visible to the value of the parameter. 0 for invisible, non-zero for visible.
	bool isVisible() - returns the current value of the data item visible
	SetAnimation(int) - starts animating the sprite with a frame delay specified in the parameter
	SetFrameDelay(int) - sets the amount of delay between frames of animation
	SetFrame(int) - sets the current frame of animation to be displayed
	SetPosition(int, int) - sets the (x,y) position of the sprite on screen
	SetSize(int, int) - sets the width and height of the sprite
	int GetWidth() - gets the width, in pixels, of the sprite
	int GetHeight() - gets the height, in pixels, of the sprite
	MoveTo(int x, int y, int speed) - starts moving the sprite to location (x,y) at the specified speed
	Update() - updates the sprite's information each tick of the game, especially x and y for moving sprites
	Draw(BITMAP *frame, BITMAP *buffer) - draws the BITMAP frame to the BITMAP buffer
	int GetFrameNum	() - returns the value in currFrame
	SetFrameCount(int) - sets the value of numFrames to the value of the parameter
	ChangeBitmap(std::string) - sets the data item fileRefName to the parameter's value
*/

#ifndef _SPRITE_H
#define _SPRITE_H

#include "globals.h"
#include "collidable.h"


class Sprite
{
private:
	std::string fileRefName;
	bool animating, loops;
	bool visible, alive;
	int currFrame, numFrames, frameDelay;
	bool moving;
	int rest;
	int new_x, new_y, speed;
	BoundingBox box;

	void NextFrame();
	void MovePosition();

public:
	Sprite();
	Sprite(std::string, int, int, int, int);
	~Sprite();
	std::string GetSheetRef() { return fileRefName; }
	bool isColliding(BoundingBox &box);
	bool isColliding(Sprite &other_sprite);
	bool isAnimating(void);
	bool isAlive(void);
	void SetAlive(bool);
	void SetVisible(int);
	bool isVisible();
	void SetAnimation(int);
	void SetFrameDelay(int);
	void SetFrame(int);
	void SetPosition(int, int);
	void SetSize(int, int);
	int GetWidth();
	int GetHeight();
	void MoveTo(int, int, int);
	void Update();
	void Draw(BITMAP *frame, BITMAP *buffer);
	int GetFrameNum	();
	void SetFrameCount(int);
	void ChangeBitmap(std::string);
};

#endif