#include <iostream>
#include "GameFramework.h"

/* NULL OBJECT */
GFText const GFText::null(-1, 0, 0);

/* CONSTRUCTOR */
GFText::GFText(int r, int x, int y) : GFObject(r), _x(x), _y(y) { };

/* DESTRUCTOR */
GFText::~GFText() { };

void GFText::setTextPosition(int x, int y)
{ 
	sprintf(GameFramework::_msgBuffer, "%d %d %d %d", TEXT_CHANGE_LOCATION, _ref, x, y); 
	GameFramework::sendMessage();
};

void GFText::setVisible(bool f)
{ 
	sprintf(GameFramework::_msgBuffer, "%d %d %d", TEXT_VISIBILITY_CHANGE, _ref, f); 
	GameFramework::sendMessage();
};

void GFText::setContent(std::string content)
{ 
	sprintf(GameFramework::_msgBuffer, "%d %d %s", TEXT_CHANGE_CONTENT, _ref, content.c_str()); 
	GameFramework::sendMessage();
};

/* PRINT FUNCTION */
std::ostream& operator<<(std::ostream &s, GFText &t)
{ return s << "TEXTOBJ @ " << &t << ": " << t._ref; };
