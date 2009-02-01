#include <iostream>

#include "GFSprite.h"

GFSprite const GFSprite::nul(-1, 0, 0);

GFSprite::~GFSprite()
{
	std::cerr << "ctor for GFS @ " << this << std::endl;
}
