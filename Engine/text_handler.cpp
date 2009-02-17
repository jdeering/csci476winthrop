#include "text_handler.h"

void TextHandler::ReadText(std::string refName)
{
}

TextHandler::TextHandler()
{
	numObjects = 0;
}

TextHandler::~TextHandler()
{
//	for(std::map<std::string, Text>::iterator i = text.begin(); i != text.end(); ++i)
//	{
		text.clear();			
	//}
	numObjects = 0;
}

bool TextHandler::AddText(std::string refName, std::string textString, int x, int y, bool visible)
{
	Text temp;
	if(numObjects < MAXFILES)
	{
		temp.LoadText(textString, x, y, visible);
		text[refName] = temp;
		numObjects++;
		return true;
	}
	allegro_message("Text Object %s could not be added.", refName.c_str());
	return false;
}

bool TextHandler::RemoveText(std::string refName)
{
	std::map<std::string, Text>::iterator loc = text.find(refName);
	if(numObjects > 0 && loc != text.end())
	{
		text.erase(loc);
		numObjects--;
		return true;
	}
	allegro_message("Text Object %s could not be removed.", refName.c_str());
	return false;
}


bool TextHandler::ShowText(std::string refName, BITMAP *bmp)
{
	return true;
}

void TextHandler::SetTextPosition(std::string refName, int x, int y)
{
	text[refName].SetPosition(x, y);
}
