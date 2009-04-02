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
	sprintf(_msgBuffer, "%d %d %s", SPRITE_CHANGE_BITMAP, _ref, name);
	GameFramework::Instance().sendMessage(_msgBuffer);
	_clrBuffer();
};

void GFSprite::setVisible(bool f)
{ 
	sprintf(_msgBuffer, "%d %d %d", SPRITE_VISIBILITY_CHANGE, _ref, f); 
	GameFramework::Instance().sendMessage(_msgBuffer);
	_clrBuffer();
};

void GFSprite::setSpriteSize(int w, int h)
{ 
	sprintf(_msgBuffer, "%d %d %d %d", SPRITE_SET_SIZE, _ref, w, h); 
	GameFramework::Instance().sendMessage(_msgBuffer);
	_clrBuffer();
};

void GFSprite::setSpritePosition(int x, int y)
{ 
	sprintf(_msgBuffer, "%d %d %d %d", SPRITE_SET_LOCATION, _ref, x, y); 
	GameFramework::Instance().sendMessage(_msgBuffer);
	_clrBuffer();
};

void GFSprite::moveTo(int x, int y, int speed)
{ 
	sprintf(_msgBuffer, "%d %d %d %d %d", SPRITE_MOVE_TO, _ref, x, y, speed); 
	GameFramework::Instance().sendMessage(_msgBuffer);
	_clrBuffer();
};

void GFSprite::setSpriteFrame(int frame)
{ 
	sprintf(_msgBuffer, "%d %d %d", SPRITE_SET_FRAME, _ref, frame); 
	GameFramework::Instance().sendMessage(_msgBuffer);
	_clrBuffer();
};

void GFSprite::setAnimation(bool f)
{ 
	sprintf(_msgBuffer, "%d %d %d", SPRITE_SET_ANIMATION, _ref, f); 
	GameFramework::Instance().sendMessage(_msgBuffer);
	_clrBuffer();
};

void GFSprite::setSpriteFrameDelay(int ticks)
{ 
	sprintf(_msgBuffer, "%d %d %d", SPRITE_SET_FRAME_DELAY, _ref, ticks); 
	GameFramework::Instance().sendMessage(_msgBuffer);
	_clrBuffer();
};

/* PRINT FUNCTION */
std::ostream& operator<<(std::ostream &s, GFSprite &g)
{ return s << "SPRITE @ " << &g << ": " << g._ref; };
