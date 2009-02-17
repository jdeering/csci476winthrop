#include "text.h"

ISpVoice* Text::pVoice = NULL;

Text::Text()
{
	Text::pVoice = NULL;
	x = 0; 
	y = 0; 
	visible = false;
}

Text::~Text()
{
	Text::pVoice->Release();
	Text::pVoice = NULL;
}

void Text::LoadText(std::string txt, int x_, int y_, bool vis)
{
	text = txt;
	x = x_;
	y = y_;
	visible = vis;
}

void Text::ReadText()
{	
	const std::wstring str(text.begin(), text.end());
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&Text::pVoice);
    if( SUCCEEDED( hr ) )
    {
		hr = Text::pVoice->SetRate(0);
		hr = Text::pVoice->Speak(str.c_str(), 0, NULL);
        Text::pVoice->Release();
        Text::pVoice = NULL;
    }
}

void Text::ShowText(bool read, BITMAP *dest)
{
	textout_ex(dest, font, text.c_str(), x, y, makecol(0, 0, 255), 0);
	if(read)
		ReadText();
}

void Text::SetPosition(int x_, int y_)
{
	x = x_;
	y = y_;
}