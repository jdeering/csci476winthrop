#include "text.h"


Text::Text()
{
	pVoice = NULL;
	x = 0; 
	y = 0; 
	visible = false;
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
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
    if( SUCCEEDED( hr ) )
    {
		hr = pVoice->SetRate(0);
		hr = pVoice->Speak(str.c_str(), 0, NULL);
        pVoice->Release();
        pVoice = NULL;
    }
}

void Text::ShowText(bool read, BITMAP *dest)
{
	textout_ex(dest, font, text.c_str(), x, y, makecol(0, 0, 255), 0);
	if(read)
		ReadText();
}
