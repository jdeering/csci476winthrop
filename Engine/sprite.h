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
	int frameRows, frameColumns;
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
	void SetVisible(bool);
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
	void SetColumnCount(int);
};

#endif