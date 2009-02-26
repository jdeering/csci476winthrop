#include "engine.h"
#include <iostream>

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

	if (allegro_init())
	{
		allegro_message("Allegro could not be initialized. Application Terminating.");
		return 1;
	}
	if (install_timer())
	{
		allegro_message("Failed to install timer. Application Terminating.");
		return 1;
	}
	
	for(int i = 0; i < argc; i++)
	{
		allegro_message("%s", argv[i]);
	}

	char* username = "Anonymous";
	// Get username
	if(argc > 1)
		strcpy(username, argv[1]);

   install_keyboard(); 
   install_mouse();

	/* set a graphics mode sized 800x600 */  
	int mode;
	if(!FULLSCREEN)
		mode = GFX_AUTODETECT_WINDOWED;
	else
		mode = GFX_AUTODETECT_FULLSCREEN;
	set_color_depth(16);
	if (set_gfx_mode(mode, 800, 600, 0, 0) != 0)
	{
		allegro_message("Unable to set graphic mode.\n%s\n\nApplication terminating.", allegro_error);
		return 1;
	} 

	show_mouse(screen);
    fw = Framework::Instance(username);

	while(fw->isActive())
	{
		// Set framerate to about 30 fps
		rest_callback(33, Update);
		fw->MainLoop();
	}

	// Uninitialize all Allegro devices
	remove_mouse();
	remove_keyboard();
	remove_timer();
    ::CoUninitialize();
    return EXIT_SUCCESS;
}

END_OF_MAIN()