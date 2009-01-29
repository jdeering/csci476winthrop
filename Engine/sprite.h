#ifndef _SPRITE_H
#define _SPRITE_H

#include <string>
#include "collidable.h"

class Sprite
{
private:
	std::string fileName;
	bool animating, loops, active;
	int currFrame, numFrames, frameDelay;
	int frameRows, frameColumns;
	bool moving;
	int new_x, new_y, speed;
	BoundingBox box;
	BITMAP *img;
public:
	Sprite();
	Sprite(BITMAP*, int, int, int, int);
	~Sprite();
	bool isAnimating(void);
	bool isActive(void);
	void SetActive(bool);
	void SetAnimation(int);
	void SetFrameDelay(int);
	void SetFrame(int);
	void SetPosition(int, int);
	void SetSize(int, int);
	void MoveTo(int, int, int);
	void Update();
	void SetName(char*);
	std::string GetName();
private:
	void NextFrame();
	void MovePosition();
	void Draw();
};

#endif