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
