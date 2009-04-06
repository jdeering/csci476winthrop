#include "text.h"

/******************************************************
	Default Constructor
******************************************************/
Text::Text()
{
	pVoice = NULL;
	x = 0; 
	y = 0; 
	visible = false;
}

/******************************************************
	Default Destructor
******************************************************/
Text::~Text()
{
	if(pVoice)
	{
		pVoice->Release();
		pVoice = NULL;
	}
}

/******************************************************
	Loads the values for the <code>Text</code> object

	@param txt The string to be displayed and/or read for the text object
	@param x_ The x coordinate of the text object
	@param y_ The y coordinate of the text object
	@param vis <code>true</code> if the text object should be visible, <code>false</code> otherwise
******************************************************/
void Text::LoadText(std::string txt, int x_, int y_, bool vis)
{
	text = txt;
	x = x_;
	y = y_;
	visible = vis;
}

/******************************************************
	Reads the string associated with the object using
	Windows text-to-speech
******************************************************/
void Text::ReadText()
{	
	const std::wstring str(text.begin(), text.end());
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
    if( SUCCEEDED( hr ) )
    {
		hr = pVoice->SetRate(0);
		hr = pVoice->Speak(str.c_str(), 0, NULL);
        pVoice->Release();
        pVoice = NULL;
    }
}

/******************************************************
	Displays the text on the specified BITMAP if it is
	visible and reads the text if specified to do so.

	@param read <code>true</code> if text-to-speech should be used, <code>false</code> otherwise
	@param dest Allegro BITMAP on which to display the text
******************************************************/
void Text::ShowText(bool read, BITMAP *dest)
{
	if(visible)
	{
		textout_ex(dest, font, text.c_str(), x, y, makecol(255, 255, 255), 0);
	if(read)
		ReadText();
	}
}

/******************************************************
	Sets the new position of the text on screen to (x,y)

	@param x_ New x coordinate of the text position
	@param y_ New y coordinate of the text position
******************************************************/
void Text::SetPosition(int x_, int y_)
{
	x = x_;
	y = y_;
}

/******************************************************
	Changes the text string for the object to the specified
	value.

	@param txt The new <code>string</code> to associate with the object 
******************************************************/
void Text::ChangeText(std::string txt)
{
	text = txt;
}