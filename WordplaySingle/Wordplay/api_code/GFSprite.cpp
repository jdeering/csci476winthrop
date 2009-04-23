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
	sprintf(GameFramework::_msgBuffer, "%d %d %s", SPRITE_CHANGE_BITMAP, _ref, name.c_str()); 
	//GameFramework::sendMessage();
	GameFramework::ENGINE->ChangeBitmap(GameFramework::_msgBuffer);
	_clrBuffer(GameFramework::_msgBuffer);
};

void GFSprite::setVisible(bool f)
{ 
	sprintf(GameFramework::_msgBuffer, "%d %d %d", SPRITE_VISIBILITY_CHANGE, _ref, f);  
	//GameFramework::sendMessage();
	GameFramework::ENGINE->SetSpriteVisible(GameFramework::_msgBuffer);
	_clrBuffer(GameFramework::_msgBuffer);
};

void GFSprite::setSpriteSize(int w, int h)
{ 
	sprintf(GameFramework::_msgBuffer, "%d %d %d %d", SPRITE_SET_SIZE, _ref, w, h); 
	//GameFramework::sendMessage();
	GameFramework::ENGINE->SetSpriteSize(GameFramework::_msgBuffer);
	_clrBuffer(GameFramework::_msgBuffer);
};

void GFSprite::setSpritePosition(int x, int y)
{ 
	sprintf(GameFramework::_msgBuffer, "%d %d %d %d", SPRITE_SET_LOCATION, _ref, x, y);
	_x = x;
	_y = y;
	//GameFramework::sendMessage();
	GameFramework::ENGINE->SetSpriteLocation(GameFramework::_msgBuffer);
	_clrBuffer(GameFramework::_msgBuffer);
};

void GFSprite::moveTo(int x, int y, int speed)
{ 
	sprintf(GameFramework::_msgBuffer, "%d %d %d %d %d", SPRITE_MOVE_TO, _ref, x, y, speed); 
	//GameFramework::sendMessage();
	_x = x;
	_y = y;
	GameFramework::ENGINE->MoveSprite(GameFramework::_msgBuffer);
	_clrBuffer(GameFramework::_msgBuffer);
};

void GFSprite::setSpriteFrame(int frame)
{ 
	sprintf(GameFramework::_msgBuffer, "%d %d %d", SPRITE_SET_FRAME, _ref, frame); 
	//GameFramework::sendMessage();
	GameFramework::ENGINE->SetFrame(GameFramework::_msgBuffer);
	_clrBuffer(GameFramework::_msgBuffer);
};

void GFSprite::setAnimation(bool f)
{ 
	sprintf(GameFramework::_msgBuffer, "%d %d %d", SPRITE_SET_ANIMATION, _ref, f); 
	//GameFramework::sendMessage();
	GameFramework::ENGINE->SetAnimation(GameFramework::_msgBuffer);
	_clrBuffer(GameFramework::_msgBuffer);
};

void GFSprite::setSpriteFrameDelay(int ticks)
{ 
	sprintf(GameFramework::_msgBuffer, "%d %d %d", SPRITE_SET_FRAME_DELAY, _ref, ticks);
	//GameFramework::sendMessage();
	GameFramework::ENGINE->SetFrameDelay(GameFramework::_msgBuffer);
	_clrBuffer(GameFramework::_msgBuffer);
};

/* PRINT FUNCTION */
std::ostream& operator<<(std::ostream &s, GFSprite &g)
{ return s << "SPRITE @ " << &g << ": " << g._ref; };
