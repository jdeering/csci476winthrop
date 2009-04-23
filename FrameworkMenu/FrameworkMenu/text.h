/*
Jason Deering

text.h

This class is for use in the Framework.

It requires Allegro header files included for the BITMAP struct.

The text class implements the display and reading of text-to-speech for all 
text objects, visible or not, that are used in game modules.


DATA ITEMS
	ISpVoice* pVoice - Pointer to Windows speech voice for reading text-to-speech
	int x - x-coordinate of the text on screen
	int y - y-coordinate of text on screen
	bool visible - value set to control whether the text should be displayed and read or only read
	std::string text - the std::string of text that is being displayed and/or read

FUNCTIONS
	SetPosition(int x, int y) - sets the new on-screen text position to (x,y)
	SetVisible(int vis) - sets the visibility of the text object
	LoadText(std::string txt, , int x, int y, bool visible) - used to load the variables for the current
															class instance
	ShowText(bool read, BITMAP* dest) - displays the text onscreen, drawing to the dest BITMAP, and
											reads the associated std::string if the read parameter is true
	ReadText(std::string stringToRead, unsigned short volume) - reads stringToRead using Windows text-to-speech
																at the specified volume
	ChangeText(std::string) - takes a std::string as input to change the text variable associated with the
						   class instance

*/


#ifndef _TEXT_H
#define _TEXT_H

#include "globals.h"


class Text
{
private:	
	static ISpVoice *pVoice;
	int x, y;
	int size; // height in pixels
	int color, bg_color; // Foreground and background colors
	bool visible;
	std::string text;
public:
	Text();
	~Text();
	void SetPosition(int x_, int y_);
	void SetVisible(int vis);
	void LoadText(std::string txt, int x_, int y_, bool visible);
	void ShowText(bool read, BITMAP *dest);
	void ChangeText(std::string txt);
	void SetSize(int);
	void SetColor(int r, int g, int b);
	void SetBackgroundColor(int r, int g, int b);
	
	static void ReadText(std::string, unsigned short);
};


#endif
