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
