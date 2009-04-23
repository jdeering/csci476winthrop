#include "text.h"

ISpVoice* Text::pVoice = NULL;

/******************************************************
	Default Constructor
******************************************************/
Text::Text()
{
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

	@param txt The std::string to be displayed and/or read for the text object
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
	Reads the string parameter using Windows text-to-speech

	@param stringToRead The string to be read via text-to-speech.
	@param volume Volume value (0-100)
******************************************************/
void Text::ReadText(std::string stringToRead, unsigned short volume)
{
	const std::wstring str(stringToRead.begin(), stringToRead.end());
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
    if( SUCCEEDED( hr ) )
    {
		hr = pVoice->SetRate(0);
		hr = pVoice->SetVolume(volume);
		hr = pVoice->Speak(str.c_str(), 0, NULL);
        pVoice->Release();
        pVoice = NULL;
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
	Changes the text std::string for the object to the specified
	value.

	@param txt The new <code>std::string</code> to associate with the object 
******************************************************/
void Text::ChangeText(std::string txt)
{
	text = txt;
}

/******************************************************
	Displays the text on the specified BITMAP if it is
	visible and reads the text if specified to do so.

	@param read <code>true</code> if text-to-speech should be used, <code>false</code> otherwise
	@param dest Allegro BITMAP on which to display the text
******************************************************/
void Text::ShowText(bool read, BITMAP *dest)
{
	double multiplier = size / 8.0; // Regular font size is 8 pixels, set multiplier to scale up to size
	BITMAP *tmp;

	tmp = create_bitmap(text_length(font, text.c_str()), text_height(font));

	if(!tmp)
	{
		allegro_message("Error creating font for text object.");
		return;
	}

	clear_to_color(tmp, makecol(255, 0, 255));
	textout_ex(tmp, font, text.c_str(), 0, 0, color, bg_color);

	masked_stretch_blit(tmp, dest, 0, 0, tmp->w, tmp->h, x+XOFFSET, y, (int)(tmp->w * multiplier), (int)(tmp->h * multiplier));
	
	destroy_bitmap(tmp);
	
}

/******************************************************
	Changes the pixel size of the text object for display.

	@param sz The pixel size for the text object.	
******************************************************/
void Text::SetSize(int sz)
{
	size = sz;
}

/******************************************************
	Changes the foreground color of the text object for display.

	@param r The amount of red (0-255) in the RGB color.	
	@param g The amount of green (0-255) in the RGB color.
	@param b The amount of blue (0-255) in the RGB color.
******************************************************/
void Text::SetColor(int r, int g, int b)
{
	// Maintain correct ranges
	if(r < 0) r = 0;
	if(g < 0) g = 0;
	if(b < 0) b = 0;
	if(r > 255) r = 255;
	if(g > 255) g = 255;
	if(b > 255) b = 255;

	color = makecol(r, g, b);
}

/******************************************************
	Changes the background color of the text object for display.

	@param r The amount of red (0-255) in the RGB color.	
	@param g The amount of green (0-255) in the RGB color.
	@param b The amount of blue (0-255) in the RGB color.
******************************************************/
void Text::SetBackgroundColor(int r, int g, int b)
{
	// Maintain correct ranges
	if(r < 0) r = 0;
	if(g < 0) g = 0;
	if(b < 0) b = 0;
	if(r > 255) r = 255;
	if(g > 255) g = 255;
	if(b > 255) b = 255;

	bg_color = makecol(r, g, b);
}

/******************************************************
	Changes the visibility of the text object.

	@param vis The new visibilty. 0 for invisible, non-zero for visible.	
******************************************************/
void Text::SetVisible(int vis)
{
	if(vis == 0)
		visible = false;
	else
		visible = true;
}