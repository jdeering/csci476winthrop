#include "text_handler.h"

TextHandler::TextHandler()
{
	numObjects = 0;
	readEnabled = false;
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

bool TextHandler::AddText(std::string refName, const char* inString, int x, int y, bool visible)
{
	Text temp;
	std::string textString = inString;
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

bool TextHandler::AddTextByRef(std::string refName, std::string assetName, int x, int y, bool visible)
{
	if(numObjects < MAXFILES)
	{
		if(refName != assetName)
		{
			text[refName] = text[assetName];
			numObjects++;
			return true;
		}
		else
		{
			allegro_message("Text Object reference already exists.");
			return false;
		}
	}
	allegro_message("Text Object %s could not be added.", refName.c_str());
	return false;
}

bool TextHandler::ChangeText(std::string refName, std::string textString)
{
	text[refName].ChangeText(textString);
	return true;
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


bool TextHandler::ShowText(std::string refName, int setVisible, BITMAP *bmp)
{
	if(setVisible)
		text[refName].ShowText(readEnabled, bmp);
	if(readEnabled)
		ReadText(refName);

	return true;
}

void TextHandler::SetTextPosition(std::string refName, int x, int y)
{
	text[refName].SetPosition(x, y);
}

void TextHandler::SetTTS(bool TTS)
{
	readEnabled = TTS;
}

void TextHandler::ReadText(std::string refName)
{
	text[refName].ReadText();
}


void TextHandler::ShowAllVisible(BITMAP* dest)
{
	for(std::map<std::string, Text>::iterator i = text.begin(); i != text.end(); ++i)
	{
		i->second.ShowText(readEnabled, dest);
	}
}