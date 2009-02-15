#ifndef _TEXT_HANDLER_H
#define _TEXT_HANDLER_H

#include "text.h"

class TextHandler
{
private:
	std::map<std::string, Text> text;
	void ReadText(std::string refName);
public:
	TextHandler(){}
	~TextHandler(){}
	bool AddText(std::string refName, std::string textString, int x, int y, bool visible);
	bool RemoveText(std::string refName);
	bool ShowText(std::string refName, BITMAP *bmp){return true;}
	void SetTextPosition(std::string refName, int x, int y){}
};


#endif