#include <iostream>

#include "GFAudio.h"

/* NULL OBJECT */
GFAudio const GFAudio::null(-1);

/* DESTRUCTOR */
GFAudio::~GFAudio() { };

/* CONSTRUCTOR */
GFAudio::GFAudio(int r) : _ref(r) { };

 /* 
	A QUICK COMMENT ABOUT THIS OPERATOR:
	there should be no case where this operator is EVER true, except in the case
	where a function return value is checked against null. for that reason, this
	operator serves only to service the needs of error checking.
 */
bool GFAudio::operator==(const GFAudio &a)
{ return _ref == a._ref; };

/* PRINT FUNCTION */
std::ostream& operator<<(std::ostream &s, GFAudio &a)
{ return s << "AUDIO @ " << &a << ": " << a._ref; };
