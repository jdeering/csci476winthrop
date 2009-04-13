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
	//GameFramework::sendMessage();
	GameFramework::ENGINE->SetTextPosition(GameFramework::_msgBuffer);
	_clrBuffer(GameFramework::_msgBuffer);
};

void GFText::setVisible(bool f)
{ 
	sprintf(GameFramework::_msgBuffer, "%d %d %d", TEXT_VISIBILITY_CHANGE, _ref, f);  
	//GameFramework::sendMessage();
	GameFramework::ENGINE->SetTextVisible(GameFramework::_msgBuffer);
	_clrBuffer(GameFramework::_msgBuffer);
};

void GFText::setContent(std::string content)
{ 
	sprintf(GameFramework::_msgBuffer, "%d %d %s", TEXT_CHANGE_CONTENT, _ref, content.c_str());  
	//GameFramework::sendMessage();
	GameFramework::ENGINE->ChangeText(GameFramework::_msgBuffer);
	_clrBuffer(GameFramework::_msgBuffer);
};

/* PRINT FUNCTION */
std::ostream& operator<<(std::ostream &s, GFText &t)
{ return s << "TEXTOBJ @ " << &t << ": " << t._ref; };
