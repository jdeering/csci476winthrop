#include "allegro.h"
#include "winalleg.h"
#include "sapi.h"
#include <iostream>
#include <string>
#include "sprite.h"
using namespace std;

#define FULLSCREEN 0

void setText(const char*, int, int, int, bool);
void readText(const std::wstring);
std::wstring getWChar(const std::string&);

#define BUFSIZE 4096

ISpVoice * pVoice = NULL;

int main(int argc, char* argv[])
{
	char file[] = "images/mainMenu.bmp";
	
    if (FAILED(::CoInitialize(NULL)))
        return FALSE;

	if (allegro_init() != 0)
      return 1;

	
	BITMAP *image = load_bitmap(file, NULL);
	if(!image)
	{
		allegro_message("load_bitmap failed.");
		return 1;
	}
	Sprite mySprite(image, 0, 0, 800, 600);
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


   /* clear the screen to white */
   clear_to_color(screen, makecol(255, 255, 255));


	/* you don't need to do this, but on some platforms (eg. Windows) things
	* will be drawn more quickly if you always acquire the screen before
	* trying to draw onto it.
	*/
	acquire_screen();
   /* write some text to the screen with black letters and transparent background */
	mySprite.SetActive(true);
	mySprite.Update();
	//setText("Hello", SCREEN_W/2, SCREEN_H/2, makecol(255,255,255), true);
   /* you must always release bitmaps before calling any input functions */
   release_screen();

   

   /* wait for a key press */
   readkey();
	destroy_bitmap(image);
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