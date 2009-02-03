#include <iostream>

#include "GFText.h"

/* NULL OBJECT */
GFText const GFText::null(-1, 0, 0);

/* DESTRUCTOR */
GFText::~GFText() { };

/* CONSTRUCTOR */
GFText::GFText(int r, int x, int y) : _ref(r), _x(x), _y(y) { };

 /* 
	A QUICK COMMENT ABOUT THIS OPERATOR:
	there should be no case where this operator is EVER true, except in the case
	where a function return value is checked against null. for that reason, this
	operator serves only to service the needs of error checking.
 */
bool GFText::operator==(const GFText &t)
{ return _ref == t._ref; };

/* PRINT FUNCTION */
std::ostream& operator<<(std::ostream &s, GFText &t)
{ return s << "TEXTOBJ @ " << &t << ": " << t._ref; };
