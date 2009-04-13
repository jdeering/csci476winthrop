/*
Jason Deering

text_handler.h

This class is for use in the Framework.

The TextHandler class controls the display and text-to-speech reading of all text objects.


DATA ITEMS
	std::map<std::string, Text> text - container for all text objects, mapped to key values of type std::string
	int numObjects
	bool readEnabled

PRIVATE FUNCTIONS
	void ReadText(std::string refName) - reads the text object at key refName using text-to-speech

PUBLIC FUNCTIONS
	bool AddText(std::string refName, std::string textstd::string, int x, int y, bool visible) - adds a text object to the container
					using the textstd::string parameter as the text object's std::string
	bool AddText(std::string refName, const char* instd::string, int x, int y, bool visible) - adds a text object to the container
					using the instd::string parameter as the text object's std::string
	bool AddTextByRef(std::string refName, std::string assetName, int x, int y, bool visible) - adds a text object to the container
					using a std::string specified in the XML text asset reference file
	bool ChangeText(std::string refName, std::string textstd::string) - changes the std::string of the text object at key refName
	bool RemoveText(std::string refName) - removes the text object at key refName from the container
	bool ShowText(std::string refName, int setVisible, BITMAP *bmp) - displays the referenced text object
	void SetTextPosition(std::string refName, int x, int y) - changes the x,y position of the text object
	void SetSize(std::string refName, int sz) - changes the pixel size of the text object
	void SetColor(std::string refName, int r, int g, int b) - changes the foreground color of the text object
	void SetBackgroundColor(std::string refName, int r, int g, int b) - changes the background color of the text object
	void SetVisible(std::string refName, int vis) - changes the visibility of the text object
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
	void SetSize(std::string refName, int sz);
	void SetColor(std::string refName, int r, int g, int b);
	void SetBackgroundColor(std::string refName, int r, int g, int b);
	void SetVisible(std::string refName, int vis);
	void SetTTS(bool TTS);
	void ShowAllVisible(BITMAP* dest);
};


#endif
