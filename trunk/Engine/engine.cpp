#include "engine.h"
Framework* Framework::inst = NULL;

Framework* Framework::Instance(char* user)
{
	allegro_message("FI");
	std::string tempUsername = user;
	allegro_message("user copied");
	if(!Framework::inst)
	{
		allegro_message("calling constructor");
		Framework::inst = new Framework(tempUsername);
	}
	return Framework::inst;
}

Framework::Framework()
{
	buffer = create_bitmap(800, 600);
	gameRunning = false;
	username = "Anonymous";
	active = true;
	gameCount = 0;
	options.VOLUME = 128;
	options.TTS = false;
	LoadGames();
	std::string menu = "MenuImages.xml";
	LoadImages(menu);
	DrawMenu();
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
	std::string menu = "MenuImages.xml";
	LoadImages(menu);
	DrawMenu();
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

void Framework::MessageLoop()
{
	if(key[KEY_ESC])
	{
		gameRunning = false;
		active = false;
	}

	UpdateSprites();
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
	gameRunning = true;
}

void Framework::LoadGames()
{	
	gameList.Load(TEXT("Games.xml"));
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
	test = ReadFile(hStdIn_Parent, incMessage, MAX_MESSAGE_SIZE, &bytesRead, NULL);

	std::stringstream stream;
	stream.str(incMessage);
	int code;
	stream >> code;
	switch(code)
	{
		// Sprites
	case 301 : CreateSprite(stream); break;
	case 302 : CreateSpriteRefDimensions(stream); break;
	case 303 : KillSprite(stream); break;
	case 304 : ShowSprite(stream); break;
	case 305 : SetSpriteSize(stream); break;
	case 306 : SetSpriteLocation(stream); break;
	case 307 : SetFrameDelay(stream); break;
	case 308 : SetAnimation(stream); break;
	case 309 : SetFrame(stream); break;
	case 310 : MoveSprite(stream); break;
		// Text
	case 401 : SetTextPosition(stream); break;
	case 402 : ShowText(stream); break;
		// Audio
	case 501 : PlayFile(stream); break;
	case 502 : ResetLoop(stream); break;
	case 503 : StopFile(stream); break;
		// Score
	case 601 : PostScore(stream); break;
	default : allegro_message("Code %d not recognized.", code); break;
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

void Framework::CreateSprite(std::stringstream &stream)
{
	int x, y, w, h;
	std::string reference, imageReference;
	stream >> reference >> imageReference >> x >> y >> w >> h;
	sprites.AddSprite(reference, imageReference, x, y, w, h);
}

void Framework:: CreateSpriteRefDimensions(std::stringstream &stream)
{
	int x, y;
	std::string reference, imageReference;
	stream >> reference >> imageReference >> x >> y;
	sprites.AddSprite(reference, imageReference, x, y);
}


void Framework::KillSprite(std::stringstream &stream)
{
	std::string reference;
	stream >> reference;
	sprites.RemoveSprite(reference);
}

void Framework::ShowSprite(std::stringstream &stream)
{
	int vis;
	std::string reference;
	stream >> reference >> vis;
	sprites.SetVisible(reference, vis);
}

void Framework::SetSpriteSize(std::stringstream &stream)
{
	std::string reference;
	int w, h;
	stream >> reference >> w >> h;
	sprites.SetSpriteSize(reference, w, h);
}

void Framework::SetSpriteLocation(std::stringstream &stream)
{
	std::string reference;
	int x, y;
	stream >> reference >> x >> y;
	sprites.SetSpriteLocation(reference, x, y);
}

void Framework::SetFrameDelay(std::stringstream &stream)
{
	std::string reference;
	int delay;
	stream >> reference >> delay;
	sprites.SetFrameDelay(reference, delay);
}

void Framework::SetAnimation(std::stringstream &stream)
{
	std::string reference;
	int animate;
	stream >> reference >> animate;
	sprites.SetAnimation(reference, animate);
}

void Framework::SetFrame(std::stringstream &stream)
{
	std::string reference;
	int frame;
	stream >> reference >> frame;
	sprites.SetFrame(reference, frame);
}

void Framework::MoveSprite(std::stringstream &stream)
{
	std::string reference;
	int x, y, speed;
	stream >> reference >> x >> y >> speed;
	sprites.MoveSprite(reference, x, y, speed);
}

void Framework::SetTextPosition(std::stringstream &stream)
{
	std::string reference;
	int x, y;
	stream >> reference >> x >> y;
	textObjects.SetTextPosition(reference, x, y);
}

void Framework::ShowText(std::stringstream &stream)
{
	std::string reference;
	int show;
	stream >> reference >> show;
	textObjects.ShowText(reference, show, buffer);
}

void Framework::PlayFile(std::stringstream &stream)
{
	std::string reference;
	stream >> reference;
	audioObjects.PlaySample(reference, options.VOLUME); // EDIT volume
}


void Framework::ResetLoop(std::stringstream &stream)
{
	std::string reference;
	int loop;
	stream >> reference >> loop;
	audioObjects.ResetLoopFlag(reference, loop);
}

void Framework::StopFile(std::stringstream &stream)
{
	std::string reference;
	stream >> reference;
	audioObjects.StopSample(reference);
}

void Framework::PostScore(std::stringstream &stream)
{
	int score;
	stream >> score;
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