#include "engine.h"

#define FULLSCREEN 0

void setText(const char*, int, int, int, bool);
void readText(const std::wstring);
std::wstring getWChar(const std::string&);

#define BUFSIZE 4096

Framework* fw;
ISpVoice * pVoice = NULL;

void Update()
{
	fw->MessageLoop();
}

int main(int argc, char* argv[])
{
    if (FAILED(::CoInitialize(NULL)))
        return FALSE;

	if (allegro_init() != 0)
		return 1;
	if (install_timer() != 0)
		return 1;
   /* set up the keyboard handler */
   install_keyboard(); 

   /* set a graphics mode sized 800x600 */  
	int mode;
   if(!FULLSCREEN)
		mode = GFX_AUTODETECT_WINDOWED;
   else
		mode = GFX_AUTODETECT_FULLSCREEN;
	set_color_depth(16);
   if (set_gfx_mode(mode, 800, 600, 0, 0) != 0) {
	 allegro_message("Unable to set graphic mode.\n%s\n", allegro_error);
	 return 1;
   } 
   fw = Framework::Instance();

   fw->LoadImages("Images.xml");
   fw->AddSprite(100, "mainMenu", 0, 0, 400, 300);

	while(fw->isActive())
	{
		rest_callback(33, Update);
		fw->MainLoop();
	}

	remove_timer();
    ::CoUninitialize();
    return EXIT_SUCCESS;
}

END_OF_MAIN()



void setText(const char *str, int x, int y, int color, bool read)
{
	if(str != NULL)
	{
		textout_centre_ex(screen, font, str, x, y, color, -1);
		if(read)
			readText(getWChar(str));
	}
	else
		allegro_message("Invalid displayStr.\n");
}

void readText(const std::wstring str)
{
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
    if( SUCCEEDED( hr ) )
    {
		hr = pVoice->SetRate(0);
		hr = pVoice->Speak(str.c_str(), 0, NULL);
        pVoice->Release();
        pVoice = NULL;
    }
}

std::wstring getWChar(const std::string &s)
{
	 int len;
	 int slength = (int)s.length() + 1;
	 len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	 wchar_t* buf = new wchar_t[len];
	 MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	 std::wstring r(buf);
	 delete[] buf;
	 return r;
}