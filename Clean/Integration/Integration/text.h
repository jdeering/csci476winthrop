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
	string text - the string of text that is being displayed and/or read

FUNCTIONS
	SetPosition(int x, int y) - sets the new on-screen text position to (x,y)
	LoadText(string txt, , int x, int y, bool visible) - used to load the variables for the current
															class instance
	ShowText(bool read, BITMAP* dest) - displays the text onscreen, drawing to the dest BITMAP, and
											reads the associated string if the read parameter is true
	ReadText() - reads the text using Windows text-to-speech
	ChangeText(string) - takes a string as input to change the text variable associated with the
						   class instance

*/


#ifndef _TEXT_H
#define _TEXT_H

#include "globals.h"

class Text
{
private:	
	ISpVoice *pVoice;
	int x, y;
	bool visible;
	std::string text;
public:
	Text();
	~Text();
	void SetPosition(int x_, int y_);
	void LoadText(std::string txt, int x_, int y_, bool visible);
	void ShowText(bool read, BITMAP *dest);
	void ReadText();
	void ChangeText(std::string txt);
};


#endif
