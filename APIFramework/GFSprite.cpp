#include <iostream>

#include "GFSprite.h"

/* NULL OBJECT */
GFSprite const GFSprite::null(-1, 0, 0);

/* DESTRUCTOR */
GFSprite::~GFSprite() { };

/* CONSTRUCTOR */
GFSprite::GFSprite(int r, int x, int y) : _ref(r), _x(x), _y(y) { };

 /* 
	A QUICK COMMENT ABOUT THIS OPERATOR:
	there should be no case where this operator is EVER true, except in the case
	where a function return value is checked against null. for that reason, this
	operator serves only to service the needs of error checking.
 */
bool GFSprite::operator==(const GFSprite &s)
{ return _ref == s._ref; };

/* PRINT FUNCTION */
std::ostream& operator<<(std::ostream &s, GFSprite &g)
{ return s << "SPRITE @ " << &g << ": " << g._ref; };
