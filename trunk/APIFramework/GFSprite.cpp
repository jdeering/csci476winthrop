#include <iostream>
#include "GameFramework.h"

/* NULL OBJECT */
GFSprite const GFSprite::null(-1, 0, 0);

/* CONSTRUCTOR */
GFSprite::GFSprite(int r, int x, int y) : GFObject(r), _x(x), _y(y) { };

/* DESTRUCTOR */
GFSprite::~GFSprite() { };

void GFSprite::changeBitmap(std::string name)
{
	std::cout << "CHANGE BITMAP???" << std::endl;
};

void GFSprite::setVisible(bool f)
{ 
	sprintf(_msgBuffer, "%d %d %d", SPRITE_VISIBILITY_CHANGE, _ref, f); 
	GameFramework::Instance().sendMessage(_msgBuffer);
};

void GFSprite::setSpriteSize(int w, int h)
{ 
	sprintf(_msgBuffer, "%d %d %d %d", SPRITE_SET_SIZE, _ref, w, h); 
	GameFramework::Instance().sendMessage(_msgBuffer);
};

void GFSprite::setSpritePosition(int x, int y)
{ 
	sprintf(_msgBuffer, "%d %d %d %d", SPRITE_SET_LOCATION, _ref, x, y); 
	GameFramework::Instance().sendMessage(_msgBuffer);
};

void GFSprite::moveTo(int x, int y, int speed)
{ 
	sprintf(_msgBuffer, "%d %d %d %d %d", SPRITE_MOVE_TO, _ref, x, y, speed); 
	GameFramework::Instance().sendMessage(_msgBuffer);
};

void GFSprite::setSpriteFrame(int frame)
{ 
	sprintf(_msgBuffer, "%d %d %d", SPRITE_SET_FRAME, _ref, frame); 
	GameFramework::Instance().sendMessage(_msgBuffer);
};

void GFSprite::setAnimation(bool f)
{ 
	sprintf(_msgBuffer, "%d %d %d", SPRITE_SET_ANIMATION, _ref, f); 
	GameFramework::Instance().sendMessage(_msgBuffer);
};

void GFSprite::setSpriteFrameDelay(int ticks)
{ 
	sprintf(_msgBuffer, "%d %d %d", SPRITE_SET_FRAME_DELAY, _ref, ticks); 
	GameFramework::Instance().sendMessage(_msgBuffer);
};

/* PRINT FUNCTION */
std::ostream& operator<<(std::ostream &s, GFSprite &g)
{ return s << "SPRITE @ " << &g << ": " << g._ref; };
