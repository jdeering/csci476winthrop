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
	void ReadText();
public:
	Text();
	void LoadText(std::string txt, int x_, int y_, bool visible);
	void ShowText(bool read, BITMAP *dest);
};


#endif