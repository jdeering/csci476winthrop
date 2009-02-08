#ifndef _SPRITE_H
#define _SPRITE_H

#include "globals.h"
#include "collidable.h"

class Sprite
{
private:
	std::string fileRefName;
	bool animating, loops, active;
	int currFrame, numFrames, frameDelay;
	int frameRows, frameColumns;
	bool moving;
	int rest;
	int new_x, new_y, speed;
	BoundingBox box;
public:
	Sprite();
	Sprite(std::string, int, int, int, int);
	~Sprite();
	std::string GetSheetRef() { return fileRefName; }
	bool isAnimating(void);
	bool isActive(void);
	void SetActive(bool);
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
private:
	void NextFrame();
	void MovePosition();
};

#endif