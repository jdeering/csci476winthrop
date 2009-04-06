/*
Jason Deering

text_handler.h

This class is for use in the Framework.

The TextHandler class controls the display and text-to-speech reading of all text objects.


DATA ITEMS
	map<string, Text> text - container for all text objects, mapped to key values of type string
	int numObjects
	bool readEnabled

PRIVATE FUNCTIONS
	void ReadText(string refName) - reads the text object at key refName using text-to-speech

PUBLIC FUNCTIONS
	bool AddText(string refName, string textString, int x, int y, bool visible) - adds a text object to the container
					using the textString parameter as the text object's string
	bool AddText(string refName, const char* inString, int x, int y, bool visible) - adds a text object to the container
					using the inString parameter as the text object's string
	bool AddTextByRef(string refName, string assetName, int x, int y, bool visible) - adds a text object to the container
					using a string specified in the XML text asset reference file
	bool ChangeText(string refName, string textString) - changes the string of the text object at key refName
	bool RemoveText(string refName) - removes the text object at key refName from the container
	bool ShowText(string refName, int setVisible, BITMAP *bmp) -
	void SetTextPosition(string refName, int x, int y) - 
	void SetTTS(bool TTS) - sets the text-to-speech flag
	void ShowAllVisible(BITMAP* dest) - displays all visible text objects on the dest BITMAP

*/

#ifndef _TEXT_HANDLER_H
#define _TEXT_HANDLER_H

#include "text.h"

class TextHandler
{
private:
	std::map<std::string, Text> text;
	void ReadText(std::string refName);
	int numObjects;
	bool readEnabled;
public:
	TextHandler();
	~TextHandler();
	bool AddText(std::string refName, std::string textString, int x, int y, bool visible);
	bool AddText(std::string refName, const char* inString, int x, int y, bool visible);
	bool AddTextByRef(std::string refName, std::string assetName, int x, int y, bool visible);
	bool ChangeText(std::string refName, std::string textString);
	bool RemoveText(std::string refName);
	bool ShowText(std::string refName, int setVisible, BITMAP *bmp);
	void SetTextPosition(std::string refName, int x, int y);
	void SetTTS(bool TTS);
	void ShowAllVisible(BITMAP* dest);
};


#endif
