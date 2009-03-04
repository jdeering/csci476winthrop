#include "engine.h"
Framework* Framework::inst = NULL;

Framework* Framework::Instance(std::string user)
{
	if(!Framework::inst)
	{
		Framework::inst = new Framework(user);
	}
	return Framework::inst;
}

Framework::Framework()
{
	gameRunning = false;
	username = "Anonymous";
	active = true;
	gameCount = 0;
	options.VOLUME = 128;
	options.TTS = false;
}

Framework::Framework(std::string user)
{
	buffer = create_bitmap(800, 600);
	gameRunning = false;
	username = user;
	active = true;
	gameCount = 0;
	options.VOLUME = 128;
	options.TTS = false;
	LoadGames();
	std::string menu = "data/MenuImages.xml";
	LoadImages(menu);
	DrawMenu();
	allegro_message("Game Launching");
	LaunchGame(0);
}

Framework::~Framework()
{
	show_mouse(NULL);
	for(int i = 0; i < gameCount; i++)
		destroy_bitmap(games[i].icon);
	destroy_bitmap(buffer);
	active = false;
}


void Framework::LoadImages(std::string file_name)
{
	std::wstring file(file_name.begin(), file_name.end());
	imgXML.Load(file.c_str());
	LoadImages();
}

void Framework::LoadAudio(std::string file_name)
{
	std::wstring file(file_name.begin(), file_name.end());
	audXML.Load(file.c_str());
	LoadAudio();
}

void Framework::LoadText(std::string file_name)
{
	std::wstring file(file_name.begin(), file_name.end());
	txtXML.Load(file.c_str());
	LoadText();
}

void Framework::LoadImages()
{
	imgXML.FindElem();

	while(imgXML.FindChildElem(TEXT("image")))
	{
		imgXML.IntoElem();
		// Get attributes
		std::wstring atFile = imgXML.GetAttrib(TEXT("file"));
		std::wstring atRef = imgXML.GetAttrib(TEXT("ref"));
		std::wstring atNumFrames = imgXML.GetAttrib(TEXT("numFrames"));
		std::wstring atNumFrameCol = imgXML.GetAttrib(TEXT("numFrameCol"));
		std::wstring atWidth = imgXML.GetAttrib(TEXT("frameWidth"));
		std::wstring atHeight = imgXML.GetAttrib(TEXT("frameHeight"));
		// Set variables for attributes
		std::string file(atFile.begin(), atFile.end());
		std::string ref(atRef.begin(), atRef.end());
		std::string numFrames(atNumFrames.begin(), atNumFrames.end());
		std::string numFrameCol(atNumFrameCol.begin(), atNumFrameCol.end());
		std::string width(atWidth.begin(), atWidth.end());
		std::string height(atHeight.begin(), atHeight.end());
		imgXML.OutOfElem();
		
		// Add file to sprite handler
		sprites.AddFile(ref, file, atoi(numFrames.c_str()), atoi(numFrameCol.c_str()), atoi(width.c_str()), atoi(height.c_str()));
	}
}

void Framework::LoadAudio()
{
	SAMPLE *temp = NULL;
	audXML.FindElem();
	bool loopVal = false;
	while(audXML.FindChildElem(TEXT("audio")))
	{
		audXML.IntoElem();
		// Get attributes
		std::wstring atFile = audXML.GetAttrib(TEXT("file"));
		std::wstring atRef = audXML.GetAttrib(TEXT("ref"));
		std::wstring atLoop = audXML.GetAttrib(TEXT("loop"));

		// Set variables for attributes
		std::string file(atFile.begin(), atFile.end());
		std::string ref(atRef.begin(), atRef.end());
		std::string loop(atLoop.begin(), atLoop.end());
		audXML.OutOfElem();

		if(strcmp(loop.c_str(), "true") == 0)
			loopVal = true;
		else if(strcmp(loop.c_str(), "false") == 0)
			loopVal = false;
		else
		{
			allegro_message("Error in Audio XML file (loop value).");
			return;
		}

		temp = load_sample(file.c_str());
		if(!temp)
		{
			allegro_message("File not found. Audio Sample %s not added.", ref);
		}
		else
			audioObjects.AddSample(ref, temp, loopVal);
	}
	destroy_sample(temp);
}

void Framework::LoadText()
{
	txtXML.FindElem();
	int x, y;
	bool visVal = false;
	while(txtXML.FindChildElem(TEXT("text")))
	{
		x=0; y=0;
		txtXML.IntoElem();
		// Get attributes
		std::wstring atString = txtXML.GetAttrib(TEXT("string"));
		std::wstring atRef = txtXML.GetAttrib(TEXT("ref"));
		std::wstring atX = txtXML.GetAttrib(TEXT("x"));
		std::wstring atY = txtXML.GetAttrib(TEXT("y"));
		std::wstring atVisible = txtXML.GetAttrib(TEXT("visible"));

		// Set variables for attributes
		std::string textString(atString.begin(), atString.end());
		std::string ref(atRef.begin(), atRef.end());
		std::string xLoc(atX.begin(), atX.end());
		std::string yLoc(atY.begin(), atY.end());
		std::string visible(atVisible.begin(), atVisible.end());
		txtXML.OutOfElem();
		x = atoi(xLoc.c_str());
		y = atoi(yLoc.c_str());

		if(strcmp(visible.c_str(), "true") == 0)
			visVal = true;
		else if(strcmp(visible.c_str(), "false") == 0)
			visVal = false;
		else
		{
			allegro_message("Error in Audio XML file (loop value).");
			return;
		}

//		textObjects.AddText(ref, textString, x, y, visVal);
	}
}

void Framework::UpdateSprites()
{
	scare_mouse();
	clear_to_color(buffer, makecol(0, 0, 255));
	sprites.DrawSprites(buffer);
	unscare_mouse();
}


void Framework::UpdateText()
{
}

void Framework::MessageLoop()
{
	if(key[KEY_ESC])
	{
		gameRunning = false;
		active = false;
	}

	UpdateSprites();
	UpdateText();
	UpdateMouse();
	UpdateKeyboard();
	UpdateOptions();
	if(gameRunning)
	{
		GetMessage();		
	}
	CheckErrors();
}

void Framework::MainLoop()
{
	MessageLoop();
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, 800, 600);
	release_screen();
}

void Framework::CreateMessagePipes()
{
	SECURITY_ATTRIBUTES saAttr;	
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	saAttr.bInheritHandle = TRUE; 
	saAttr.lpSecurityDescriptor = NULL;

	// Create a pipe for the child process's STDOUT. 

	if ( ! CreatePipe(&hStdIn_Parent, &hStdOut_Child, &saAttr, 0) ) 
		allegro_message("Error creating output pipe.");

	// Ensure the read handle to the pipe for STDOUT is not inherited.

	if ( ! SetHandleInformation(hStdIn_Parent, HANDLE_FLAG_INHERIT, 0) )
		allegro_message("Error setting handle information.");

	// Create a pipe for the child process's STDIN. 

	if ( ! CreatePipe(&hStdOut_Parent, &hStdIn_Child, &saAttr, 0) ) 
		allegro_message("Error creating input pipe.");

	// Ensure the write handle to the pipe for STDIN is not inherited.

	if ( ! SetHandleInformation(hStdOut_Parent, HANDLE_FLAG_INHERIT, 0) )
		allegro_message("Error setting handle information.");
}

void Framework::LaunchGame(int gameNum)
{
	CreateMessagePipes();
	TCHAR szCmdline[]=TEXT("C:\\Users\\Deering\\Documents\\Visual Studio 2005\\Projects\\WordPlayNew\\debug\\WordPlayNew.exe");
	CreateGameProcess(szCmdline);
	gameRunning = true;
}

void Framework::LoadGames()
{	
	gameList.Load(TEXT("data/Games.xml"));
	gameList.FindElem();

	while(gameList.FindChildElem(TEXT("game")) && gameCount < 4)
	{
		gameList.IntoElem();
		// Get attributes
		std::wstring atPath = gameList.GetAttrib(TEXT("path"));
		std::wstring atName = gameList.GetAttrib(TEXT("name"));
		// Get Asset XML File Paths
		gameList.FindChildElem(TEXT("imageFile"));
		std::wstring atImageXMLPath = gameList.GetChildData();
		gameList.FindChildElem(TEXT("audioFile"));
		std::wstring atAudioXMLPath = gameList.GetChildData();		
		gameList.FindChildElem(TEXT("textFile"));
		std::wstring atTextXMLPath = gameList.GetChildData();
		gameList.FindChildElem(TEXT("icon"));
		std::wstring atIconWidth = gameList.GetChildAttrib(TEXT("width"));
		std::wstring atIcondHeight = gameList.GetChildAttrib(TEXT("height"));
		std::wstring atIconPath = gameList.GetChildData();
		gameList.OutOfElem();

		// Set variables for attributes
		std::string path(atPath.begin(), atPath.end());
		std::string name(atName.begin(), atName.end());
		std::string image(atImageXMLPath.begin(), atImageXMLPath.end());
		std::string audio(atAudioXMLPath.begin(), atAudioXMLPath.end());
		std::string text(atTextXMLPath.begin(), atTextXMLPath.end());
		std::string iconPath(atIconPath.begin(), atIconPath.end());
		games[gameCount].path = path;
		games[gameCount].name = name;
		games[gameCount].imageFile = image;
		games[gameCount].audioFile = audio;
		games[gameCount].textFile = text;
		games[gameCount].icon = load_bitmap(iconPath.c_str(), NULL);
		gameCount++;
	}
}

void Framework::LaunchGame(std::string appPath)
{ 
	std::wstring szCmdline(appPath.begin(), appPath.end());
	PROCESS_INFORMATION piProcInfo; 
	STARTUPINFO siStartInfo;
	BOOL bSuccess = FALSE; 

	// Set up members of the PROCESS_INFORMATION structure. 

	ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );

	// Set up members of the STARTUPINFO structure. 
	// This structure specifies the STDIN and STDOUT handles for redirection.

	ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO); 
	siStartInfo.hStdError = hStdOut_Child;
	siStartInfo.hStdOutput = hStdOut_Child;
	siStartInfo.hStdInput = hStdIn_Child;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	// Create the child process. 

	bSuccess = CreateProcess(szCmdline.c_str(), 
	NULL,     // command line 
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
	allegro_message("Game could not launch.");
	else 
	{
	// Close handles to the child process and its primary thread.
	// Some applications might keep these handles to monitor the status
	// of the child process, for example. 

	CloseHandle(piProcInfo.hProcess);
	CloseHandle(piProcInfo.hThread);
	}
}


void Framework::GetMessage()
{
	bool test;
	DWORD bytesRead;
	if(ReadFile(hStdIn_Parent, incMessage, MAX_MESSAGE_SIZE, &bytesRead, NULL))
	{
		allegro_message("Bytes Read : %d\n", bytesRead);
		printf("Message : %s\n", incMessage);
		int code;
		allegro_message("reading code");
		sscanf(incMessage, "%d", &code);
		allegro_message("Code = %d", code);
		switch(code)
		{
			// Sprites
		case SPRITE_CREATE : CreateSprite(incMessage); break;
		case SPRITE_CREATE_FROM_ASSET : CreateSpriteRefDimensions(incMessage); break;
		case SPRITE_REMOVE : KillSprite(incMessage); break;
		case SPRITE_VISIBILITY_CHANGE : ShowSprite(incMessage); break;
		case SPRITE_SET_SIZE : SetSpriteSize(incMessage); break;
		case SPRITE_SET_LOCATION : SetSpriteLocation(incMessage); break;
		case SPRITE_SET_FRAME_DELAY : SetFrameDelay(incMessage); break;
		case SPRITE_SET_ANIMATION : SetAnimation(incMessage); break;
		case SPRITE_SET_FRAME : SetFrame(incMessage); break;
		case SPRITE_MOVE_TO : MoveSprite(incMessage); break;
			// Text
		case TEXT_CREATE_FROM_ASSET	: CreateTextFromRef(incMessage); break;
		case TEXT_CREATE_FROM_STRING : CreateTextFromString(incMessage); break; 
		case TEXT_REMOVE : RemoveText(incMessage); break;
		case TEXT_CHANGE_CONTENT : ChangeText(incMessage); break;
		case TEXT_CHANGE_LOCATION : SetTextPosition(incMessage); break;
		case TEXT_VISIBILITY_CHANGE : ShowText(incMessage); break;
			// Audio
		case AUDIO_PLAY	: PlayFile(incMessage); break;		 
		case AUDIO_SET_LOOP_COUNT : ResetLoop(incMessage); break;
		case AUDIO_STOP	: StopFile(incMessage); break;
			// Score
		case SCORE : PostScore(incMessage); break;
		default : break;
		}
	}
}

void Framework::SendMessage(const char *msg)
{
	DWORD bytesWritten;
	std::string message(msg);
	WriteFile(hStdOut_Parent, message.c_str(), message.size(), &bytesWritten, NULL);
}

void Framework::AddSprite(std::string refName, std::string imageRef, int x, int y, int w, int h)
{ 
	sprites.AddSprite(refName, imageRef, x, y, w, h); 
}

void Framework::CreateSprite(char *msg)
{
	int x, y, w, h;
	char reference[25], imageReference[25];
	allegro_message("Creating Sprite");
	sscanf(msg, "%*d %s %s %d %d %d %d", reference, imageReference, &x, &y, &w, &h);
	std::string str_reference = reference;
	std::string str_imageReference = imageReference;
	printf("sprites.AddSprite(%s, %s, %d, %d, %d, %d)\n", reference, imageReference, x, y, w, h);	
	sprites.AddSprite(str_reference, str_imageReference, x, y, w, h);
}

void Framework:: CreateSpriteRefDimensions(char *msg)
{
	int x, y;
	char reference[25], imageReference[25];
	sscanf(msg, "%*d %s %s %d %d", reference, imageReference, &x, &y);
	std::string str_reference = reference;
	std::string str_imageReference = imageReference;
	sprites.AddSprite(str_reference, str_imageReference, x, y);
}


void Framework::KillSprite(char *msg)
{
	char reference[5];
	sscanf(msg, "%*d %s", reference);
	std::string str_reference = reference;
	sprites.RemoveSprite(reference);
}

void Framework::ShowSprite(char *msg)
{
	int vis;
	std::string reference;
	sscanf(msg, "%*d %s %d", reference, &vis);
	sprites.SetVisible(reference, vis);
}

void Framework::SetSpriteSize(char *msg)
{
	std::string reference;
	int w, h;
	sscanf(msg, "%*d %s %d %d", reference, &w, &h);
	sprites.SetSpriteSize(reference, w, h);
}

void Framework::SetSpriteLocation(char *msg)
{
	std::string reference;
	int x, y;
	sscanf(msg, "%*d %s %d %d", reference, &x, &y);
	sprites.SetSpriteLocation(reference, x, y);
}

void Framework::SetFrameDelay(char *msg)
{
	std::string reference;
	int delay;
	sscanf(msg, "%*d %s %d", reference, &delay);
	sprites.SetFrameDelay(reference, delay);
}

void Framework::SetAnimation(char *msg)
{
	std::string reference;
	int animate;
	sscanf(msg, "%*d %s %d", reference, &animate);
	sprites.SetAnimation(reference, animate);
}

void Framework::SetFrame(char *msg)
{
	std::string reference;
	int frame;
	sscanf(msg, "%*d %s %d", reference, &frame);
	sprites.SetFrame(reference, frame);
}

void Framework::MoveSprite(char *msg)
{
	std::string reference;
	int x, y, speed;
	sscanf(msg, "%*d %s %d %d %d", reference, &x, &y, &speed);
	sprites.MoveSprite(reference, x, y, speed);
}

void Framework::SetTextPosition(char *msg)
{
	std::string reference;
	int x, y;
	sscanf(msg, "%*d %s %d %d", reference, &x, &y);
	textObjects.SetTextPosition(reference, x, y);
}

void Framework::ShowText(char *msg)
{
	std::string reference;
	int show;
	sscanf(msg, "%*d %s %d", reference, &show);
	textObjects.ShowText(reference, show, buffer);
}

void Framework::PlayFile(char *msg)
{
	std::string reference;
	sscanf(msg, "%*d %s", reference);
	audioObjects.PlaySample(reference, options.VOLUME); // EDIT volume
}


void Framework::ResetLoop(char *msg)
{
	std::string reference;
	int loop;
	sscanf(msg, "%*d %s %d", reference, &loop);
	audioObjects.ResetLoopFlag(reference, loop);
}

void Framework::StopFile(char *msg)
{
	std::string reference;
	sscanf(msg, "%*d %s", reference);
	audioObjects.StopSample(reference);
}

void Framework::PostScore(char *msg)
{
	int score;
	sscanf(msg, "%*d %d", &score);
	gameRunning = false;
}

void Framework::UpdateMouse()
{
	std::string mouse_message = "";
	std::stringstream message;
	int button, state, x, y;
	mouse.Update(x, y);
	message.clear();
	message << "101 " << x << " " << y;
	mouse_message = message.str();
	SendMessage(mouse_message.c_str());
	message.clear();
	message.str("");
	mouse_message.clear();
	if(mouse.StateChange(button, state, x, y))
	{
		std::string sprite_name = sprites.CheckClicks(mouse.GetPointer());
		if(x >= 0 && x <= 600 && y >= 0 && y <= 600/* && gameRunning*/) // Game event
		{
			message.clear();
			message.str("");
			message << "102 " << button << " " << state << " " << x << " " << y;
			mouse_message = message.str();
			SendMessage(mouse_message.c_str());
			message.clear();
			mouse_message.clear();
			if(strcmp(sprite_name.c_str(), "") != 0)
			{				
				message.clear();
				message.str("");
				message << "103 " << button << " " << state << " " << sprite_name.c_str();
				mouse_message = message.str();
				SendMessage(mouse_message.c_str());
				message.clear();
				mouse_message.clear();
			}
		}
		else // Framework event
		{
			x += 200; // Reset x to reflect entire screen instead of only the game window
			int volumeY = 200;
			std::string sprite_name = sprites.CheckClicks(mouse.GetPointer());
			if(strcmp(sprite_name.c_str(), "exitButton") == 0)
			{
				active = false;
			}
			else if(strcmp(sprite_name.c_str(), "volumeStrip") == 0)
			{
				if(state == 1 && button == 1)
				{
					int volX = x + 200;
					if(volX > (160-25)) volX = (160-25);
					if(volX < 10) volX = 10;
					sprites.SetSpriteLocation("volumeIndicator", volX, volumeY);
					audioObjects.SetVolume(volX * 2);
				}
			}
			else
			{
			}
		}
	}
}

void Framework::UpdateKeyboard()
{
	int key, state;
	std::string key_message;
	std::stringstream message;
	while(keyboard.StateChange(key, state))
	{
		key_message.clear();
		message.clear();
		message.str("");
		message << "201 " << key << " " << state;
		key_message = message.str();
		SendMessage(key_message.c_str());
	}
}


bool Framework::isActive()
{ 
	return active;
}

bool Framework::gameIsRunning() 
{ 
	return gameRunning; 
}

void Framework::DrawMenu()
{
	sprites.AddSprite("exitButton", "exitButton", 10, 10);
	sprites.AddSprite("volumeStrip", "volumeStrip", 10, 200);
	sprites.AddSprite("volumeIndicator", "volumeIndicator", 10, 200);
	textObjects.AddText("volume", "Volume : ", 100, 100, true);
}

void Framework::CheckErrors()
{
	if(errno && errno != 2)
	{
		char* message = strerror(errno);
		allegro_message("Error %d : %s", errno, message);
	}
}

void Framework::UpdateOptions()
{	
	if(options.VOLUME < 1) options.VOLUME = 1;
	if(options.VOLUME > 255) options.VOLUME = 255;
	audioObjects.SetVolume(options.VOLUME);
	textObjects.SetTTS(options.TTS);
}

 
void Framework::CreateGameProcess(TCHAR szCmdline[])
// Create a child process that uses the previously created pipes for STDIN and STDOUT.
{ 
	
   PROCESS_INFORMATION piProcInfo;
   STARTUPINFO siStartInfo;
   BOOL bSuccess = FALSE; 
 
// Set up members of the PROCESS_INFORMATION structure. 
 
	   ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
 
// Set up members of the STARTUPINFO structure. 
// This structure specifies the STDIN and STDOUT handles for redirection.
 
   ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
   siStartInfo.cb = sizeof(STARTUPINFO); 
   siStartInfo.hStdError = hStdOut_Child;
   siStartInfo.hStdOutput = hStdOut_Child;
   siStartInfo.hStdInput = hStdIn_Child;
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
      allegro_message("Game Launch failed");
   else 
   {
      // Close handles to the child process and its primary thread.
	  // Some applications might keep these handles to monitor the status
	  // of the child process, for example. 

      CloseHandle(piProcInfo.hProcess);
      CloseHandle(piProcInfo.hThread);
   }
}


void Framework::CreateTextFromRef(char *msg)
{
	int length, x, y;
	std::string refName, assetName;
	sscanf(msg, "%*d %s %d %d %d %s", refName, &length, &x, &y, assetName);
	textObjects.AddTextByRef(refName, assetName, x, y, true);
}

void Framework::CreateTextFromString(char *msg)
{
	int length, x, y;
	std::string refName, string;
	sscanf(msg, "%*d %s %d %d %d", refName, &length, &x, &y);
	std::string str_refName = refName;
	sscanf(msg, "%*d %s %d %d %d", refName, &length, &x, &y);
	std::string str_string = string;
	textObjects.AddText(str_refName, str_string, x, y, true);
}

void Framework::RemoveText(char *msg)
{
	std::string refName;
	sscanf(msg, "%*d %s", refName);

}

void Framework::ChangeText(char *msg)
{
	
}