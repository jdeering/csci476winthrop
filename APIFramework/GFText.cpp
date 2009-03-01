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
	sprintf(_msgBuffer, "%d %d %d %d", TEXT_CHANGE_LOCATION, _ref, x, y); 
	GameFramework::Instance().sendMessage(_msgBuffer);
};

void GFText::setVisible(bool f)
{ 
	sprintf(_msgBuffer, "%d %d %d", TEXT_VISIBILITY_CHANGE, _ref, f); 
	GameFramework::Instance().sendMessage(_msgBuffer);
};

void GFText::setContent(std::string content)
{ 
	sprintf(_msgBuffer, "%d %d %s", TEXT_CHANGE_CONTENT, _ref, content.c_str()); 
	GameFramework::Instance().sendMessage(_msgBuffer);
};

/* PRINT FUNCTION */
std::ostream& operator<<(std::ostream &s, GFText &t)
{ return s << "TEXTOBJ @ " << &t << ": " << t._ref; };
