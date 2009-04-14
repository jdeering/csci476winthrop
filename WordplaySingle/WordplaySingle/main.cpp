#include <vector>
#include <string>
#include <ctime>
#include "globals.h"
#include "wordplaycontrol.h"
#include "GameFramework.h"

#define FULLSCREEN 0

void LaunchLogin();

int main(int argc, char argv[]){

    if (FAILED(::CoInitialize(NULL)))
        return FALSE;

	if (allegro_init())
	{
		printf("Allegro could not be initialized. Application Terminating.");
		return 1;
	}

	if (install_timer())
	{
		allegro_message("Failed to install timer. Application Terminating.");
		return 1;
	}
	LOCK_FUNCTION(Update);

	std::string user = "Anonymous";
	// Get username
	if(argc > 1)
		user = argv[1];

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

	GameFramework::CreateEngineInstance(user);

	//Wordplay
	WordplayControl::start();


	remove_mouse();
	remove_keyboard();
	remove_timer();
    ::CoUninitialize();

	LaunchLogin();

	return 0;	
}

void LaunchLogin()
// Create a child process that uses the previously created pipes for STDIN and STDOUT.
{ 
	TCHAR szCmdline[]=TEXT("LoginGUI.exe");
   PROCESS_INFORMATION piProcInfo;
   STARTUPINFO siStartInfo;
   BOOL bSuccess = FALSE; 
 
// Set up members of the PROCESS_INFORMATION structure. 
 
	   ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
 
// Set up members of the STARTUPINFO structure. 
// This structure specifies the STDIN and STDOUT handles for redirection.
 
   ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
   siStartInfo.cb = sizeof(STARTUPINFO); 
   siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

// Create the child process. 
    
   bSuccess = CreateProcess(NULL, 
      szCmdline,     // command line 
      NULL,          // process security attributes 
      NULL,          // primary thread security attributes 
      TRUE,          // handles are inherited 
      0,             // creation flags 
      NULL,          // use parent's environment 
      NULL,          // use parent's current directory 
      &siStartInfo,  // STARTUPINFO pointer 
      &piProcInfo);  // receives PROCESS_INFORMATION 
   
   // If an error occurs, exit the application. 
   if ( ! bSuccess ) 
      allegro_message("Login could not launch.");
   else 
   {
      // Close handles to the child process and its primary thread.
	  // Some applications might keep these handles to monitor the status
	  // of the child process, for example. 

      CloseHandle(piProcInfo.hProcess);
      CloseHandle(piProcInfo.hThread);
   }
}