#include "GameFramework.h"
#include "allegro.h"
#include <string>

void LaunchGame(int);
void LaunchLogin();

GFSprite* icons[4]; // 4 game icons
GFSprite *leftArrow, *rightArrow, *logo;
int numGames = 0;
int numPages = 0;
int gamesOnPage = 0;
int currPage = 0;
int selectedGame = -1;


void pageFlipLeft()
{
	currPage--;
	if(currPage < 0)
	{
		currPage = 0;
	}
}

void pageFlipRight()
{
	currPage++;
	if(currPage > (numPages - 1))
	{
		currPage = numPages - 1;
	}
	
}


void clickHandler(int button, int state, int x, int y)
{
	if(state) // Left or right clicks
	{
		// if left arrow clicked
		if(x >= 50 && y >= 275
			&& x <= 150 && y <= 375)
			pageFlipLeft();
		// if right arrow clicked
		if(x >= 450 && y >= 275
			&& x <= 550 && y <= 375)
			pageFlipRight();

		// icons[i] clicked
		//int i = 0;
		//selectedGame = currPage * 4 + i;
	}
}

bool mainLoop()
{
	// Update arrow visibility based on current page
	if(currPage = 0)
		leftArrow->setVisible(0);
	else
		leftArrow->setVisible(1);

	if(currPage = (numPages - 1))
		rightArrow->setVisible(0);
	else
		rightArrow->setVisible(1);

	if(selectedGame != -1)
	{
		// Stop loop
		return false;
	}
	if(currPage != (numPages - 1))
		gamesOnPage = 4;
	else
		gamesOnPage = numGames % 4;

	// display icons
	std::string assetName; // this line is necessary
	char buffer[2];
	for(int i = 0; i < gamesOnPage; i++)
	{
		assetName = "gameicon.";
		itoa((currPage * 4 + i), buffer, 10);
		// Keep these two lines
		assetName += buffer;
		strcpy(buffer, "");

		//icons[i]->changeBitmap(assetName);
		icons[i]->setVisible(1);
	}

	for(int j = gamesOnPage; j < 4; j++) // make unneeded icons invisible
		icons[j]->setVisible(0);

	return true;
}

int main()
{
    if (FAILED(::CoInitialize(NULL)))
        return FALSE;

	if (allegro_init())
	{
		printf("Allegro could not be initialized. Application Terminating.");
		return 1;
	}

   install_keyboard(); 
   install_mouse();
   if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL))
   {
	   allegro_message("Error initializing sound. Exiting the program.");
   }

	/* set a graphics mode sized 800x600 */  
	int mode = GFX_AUTODETECT_WINDOWED;
	set_color_depth(16);
	if (set_gfx_mode(mode, 800, 600, 0, 0) != 0)
	{
		allegro_message("Unable to set graphic mode.\n%s\n\nApplication terminating.", allegro_error);
		return 1;
	} 

	show_mouse(NULL);

	GameFramework::CreateEngineInstance("");

	GameFramework::mouseFunc(clickHandler);
	GameFramework::gameFunc(mainLoop);

	numGames = Framework::gameCount;
	numPages = numGames / 4 + 1;

	// Permanent asset names
	std::string background = "mainmenu_bkg";
	std::string leftArrowAsset = "leftarrow";
	std::string rightArrowAsset = "rightarrow";

	// The x and y values probably need changing for these
	logo = &GameFramework::createSprite(background, 0, 0);
	leftArrow = &GameFramework::createSprite(leftArrowAsset, 20, 275);
	rightArrow = &GameFramework::createSprite(rightArrowAsset, 480, 275);
	logo->setVisible(1);
	leftArrow->setVisible(0);
	rightArrow->setVisible(numPages);

	
	int x, y;
	for(int i = 0; i < 4; i++)
	{
		// Guessing at these values, change them as needed
		switch(i)
		{
		case 0: x = 175; y = 150; break;
		case 1: x = 400; y = 150; break;
		case 2: x = 175; y = 450; break;
		case 3: x = 400; y = 450; break;
		}
		icons[i] = &GameFramework::createSprite("leftarrow", x, y, 100, 100);
		icons[i]->setVisible(1);
	}

	// Start loop
	GameFramework::gameLoop();

	if(selectedGame != -1)
		LaunchGame(selectedGame);
	else
		LaunchLogin();

    remove_sound();
	remove_mouse();
	remove_keyboard();
    ::CoUninitialize();

	return 0;
}

void LaunchGame(int index)
{
   STARTUPINFO siStartInfo;
   PROCESS_INFORMATION piProcInfo; // maintained to close module process
   BOOL bSuccess = FALSE; 
 
// Set up members of the PROCESS_INFORMATION structure. 
 
	   ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
 
// Set up members of the STARTUPINFO structure. 
// This structure specifies the STDIN and STDOUT handles for redirection.
 
	ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO); 
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	// set the window display to HIDE
	//if(!DEBUG)
	siStartInfo.wShowWindow = SW_HIDE;

// Create the child process. 

	std::string gamePath = Framework::games[index].path + Framework::games[index].name + ".exe";
	std::wstring szCmdline(gamePath.begin(), gamePath.end());

   bSuccess = CreateProcess(NULL, 
      const_cast<LPWSTR>(szCmdline.c_str()),     // command line 
      NULL,          // process security attributes 
      NULL,          // primary thread security attributes 
      TRUE,          // handles are inherited 
      0,             // creation flags 
      NULL,          // use parent's environment 
      NULL,          // use parent's current directory 
      &siStartInfo,  // STARTUPINFO pointer 
      &piProcInfo);  // receives PROCESS_INFORMATION 

   if ( ! bSuccess ) 
      allegro_message("%s could not launch.", Framework::games[index].name.c_str());

	// Close handles to the child process and its primary thread.
	// Some applications might keep these handles to monitor the status
	// of the child process, for example. 

	CloseHandle(piProcInfo.hProcess);
	CloseHandle(piProcInfo.hThread);
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