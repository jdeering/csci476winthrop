#include "engine.h"

#define FULLSCREEN 0

Framework* fw;

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