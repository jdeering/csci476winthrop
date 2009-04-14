#include "engine.h"
#include "GameFramework.h"

Framework* Framework::inst = NULL;

Framework* Framework::Instance(std::string user)
{
	if(!inst)
	{
		inst = new Framework(user);
	}
	return inst;
}

Framework::Framework()
{
	gameRunning = false;
	username = "Anonymous";
	active = true;
	gameCount = 0;
	options.VOLUME = 128;
	options.TTS = false;
	menuRunning = true;
}

Framework::Framework(std::string user)
{
	gameRunning = false;
	username = user;
	active = true;
	gameCount = 0;
	options.VOLUME = 128;
	options.TTS = false;
	LoadGames();
	menuRunning = true;
	LaunchGame(0);
	buffer = create_bitmap(800, 600);
}

Framework::~Framework()
{
	show_mouse(NULL);
	destroy_bitmap(buffer);
	active = false;
	inst = NULL;
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
			active = false;
			return;
		}

		temp = load_sample(file.c_str());
		if(!temp)
		{
			allegro_message("File not found at \"%s\". Audio Sample \"%s\" not added.", file.c_str(), ref.c_str());
			active = false;
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
		std::wstring atString = txtXML.GetAttrib(TEXT("std::string"));
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
			active = false;
			return;
		}

		textObjects.AddText(ref, textString, x, y, visVal);
	}
}

void Framework::UpdateSprites()
{
	scare_mouse();
	clear_to_color(buffer, makecol(0, 0, 0));
	sprites.DrawSprites(buffer);
	unscare_mouse();
}


void Framework::UpdateText()
{
	textObjects.ShowAllVisible(buffer);
}

void Framework::MessageLoop()
{
	if(key[KEY_ESC] || !active)
	{
		//KillModule();
		active = false;
	}

	UpdateSprites();
	UpdateText();
	UpdateMouse();
	UpdateKeyboard();
	UpdateOptions();
	//if(gameRunning)
	//{
		//GetMessages();		
	//}
	//CheckErrors();
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
	{
		allegro_message("Error creating output pipe.");
		active = false;
	}

	// Ensure the read handle to the pipe for STDOUT is not inherited.

	if ( ! SetHandleInformation(hStdIn_Parent, HANDLE_FLAG_INHERIT, 0) )
	{
		allegro_message("Error setting handle information.");
		active = false;
	}

	// Create a pipe for the child process's STDIN. 

	if ( ! CreatePipe(&hStdIn_Child, &hStdOut_Parent, &saAttr, 0) ) 
	{
		allegro_message("Error creating input pipe.");
		active = false;
	}

	// Ensure the write handle to the pipe for STDIN is not inherited.

	if ( ! SetHandleInformation(hStdOut_Parent, HANDLE_FLAG_INHERIT, 0) )
	{
		allegro_message("Error setting handle information.");
		active = false;
	}
	
	SetNamedPipeHandleState(hStdOut_Parent, PIPE_WAIT, NULL, NULL);
}

void Framework::LaunchGame(int gameNum)
{
	LoadGameAssets(gameNum);
	//CreateMessagePipes();
	//std::string gameExe = "modules/"+games[gameNum].path + games[gameNum].name + ".exe";
	//std::wstring gameToLaunch(gameExe.begin(), gameExe.end());
	//TCHAR szCmdline[]=TEXT("modules\\Wordplay\\Wordplay.exe");
	//CreateGameProcess(gameToLaunch);
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
		std::wstring atIconHeight = gameList.GetChildAttrib(TEXT("height"));
		std::wstring atIconPath = gameList.GetChildData();
		gameList.OutOfElem();

		// Set variables for attributes
		std::string path(atPath.begin(), atPath.end());
		std::string name(atName.begin(), atName.end());
		std::string image(atImageXMLPath.begin(), atImageXMLPath.end());
		std::string audio(atAudioXMLPath.begin(), atAudioXMLPath.end());
		std::string text(atTextXMLPath.begin(), atTextXMLPath.end());
		std::string iconPath(atIconPath.begin(), atIconPath.end());
		std::string iconWidth(atIconWidth.begin(), atIconWidth.end());
		std::string iconHeight(atIconHeight.begin(), atIconHeight.end());
		games[gameCount].path = path;
		games[gameCount].name = name;
		games[gameCount].imageFile = image;
		games[gameCount].audioFile = audio;
		games[gameCount].textFile = text;
		games[gameCount].icon.path = iconPath;
		games[gameCount].icon.width = atoi(iconWidth.c_str());
		games[gameCount].icon.height = atoi(iconHeight.c_str());
		gameCount++;
	}
	for(int i = 0; i < gameCount; i++)
	{
		
		char temp[3];
		itoa(i, temp, 10);
		std::string iconName(temp);
		if(strcmp(games[i].icon.path.c_str(), "") != 0)
		{
			iconName = "gameicon." + iconName;
			sprites.AddFile(iconName, games[i].path + games[i].icon.path, games[gameCount].icon.width, games[gameCount].icon.height, 1, 1);
		}
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
	//siStartInfo.hStdError = hStdOut_Child;
	siStartInfo.hStdOutput = hStdOut_Child;
	//siStartInfo.hStdInput = hStdIn_Child;
	siStartInfo.lpTitle = L"Game Module";
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
	{
		allegro_message("Game could not launch.");
		active = false;
	}
	else 
	{
	// Close handles to the child process and its primary thread.
	// Some applications might keep these handles to monitor the status
	// of the child process, for example. 
		gameRunning = true;
	}
}


void Framework::GetMessages()
{
	DWORD bytesRead, bytesAvail, bytesLeft;
	std::stringstream msgStream;
	msgStream.clear();
	PeekNamedPipe(hStdIn_Parent, incMessage, MAX_MESSAGE_SIZE, &bytesRead, &bytesAvail, NULL);
	if (bytesRead != 0)
	{
		clearBuffer();
		if (bytesAvail > MAX_MESSAGE_SIZE)
		{
			cout << "Filled Read Pipe." << endl;
			while (bytesRead >= MAX_MESSAGE_SIZE)
			{
				clearBuffer();
				// input handle, buffer, max message size, DWORD for bytesRead
				ReadFile(hStdIn_Parent, incMessage, MAX_MESSAGE_SIZE, &bytesRead, NULL);
				msgStream.write(incMessage, bytesRead); // copy message to std::stringstream
				ParseMessage(msgStream);
			}
		}
		else 
		{
			// input handle, buffer, max message size, DWORD for bytesRead
			ReadFile(hStdIn_Parent, incMessage, MAX_MESSAGE_SIZE, &bytesRead, NULL);
			msgStream.write(incMessage, bytesRead); // copy message to std::stringstream
			ParseMessage(msgStream);
		}
	}
	clearBuffer(); // clears incMessage
}

void Framework::sendMessage(const char *msg)
{
	DWORD bytesWritten;
	std::string message(msg);
	WriteFile(hStdOut_Parent, message.c_str(), message.size(), &bytesWritten, NULL);
}


void Framework::CreateSprite(char *msg)
{
	int x, y, w, h;
	char reference[25], imageReference[25];
	sscanf(msg, "%*d %s %s %d %d %d %d", reference, imageReference, &x, &y, &w, &h);
	std::string str_reference = reference;
	std::string str_imageReference = imageReference;
	sprites.AddSprite(str_reference, str_imageReference, x+XOFFSET, y, w, h);
}

void Framework:: CreateSpriteRefDimensions(char *msg)
{
	int x, y;
	char reference[25], imageReference[25];
	sscanf(msg, "%*d %s %s %d %d", reference, imageReference, &x, &y);
	std::string str_reference = reference;
	std::string str_imageReference = imageReference;
	sprites.AddSprite(str_reference, str_imageReference, x+XOFFSET, y);
}


void Framework::KillSprite(char *msg)
{
	char reference[10];
	sscanf(msg, "%*d %s", reference);
	std::string str_reference = reference;
	if(!sprites.RemoveSprite(str_reference))
		allegro_message("Sprite %s could not be removed", str_reference.c_str());
}

void Framework::ShowSprite(char *msg)
{
	int vis;
	char reference[10];
	sscanf(msg, "%*d %s %d", reference, &vis);
	sprites.SetVisible(reference, vis);
}

void Framework::SetSpriteSize(char *msg)
{
	char reference[10];
	int w, h;
	sscanf(msg, "%*d %s %d %d", reference, &w, &h);
	sprites.SetSpriteSize(reference, w, h);
}

void Framework::SetSpriteLocation(char *msg)
{
	char reference[10];
	int x, y;
	sscanf(msg, "%*d %s %d %d", reference, &x, &y);
	printf("Setting location for %s at %d , %d\n", reference, x, y);
	sprites.SetSpriteLocation(reference, x+XOFFSET, y);
}

void Framework::SetFrameDelay(char *msg)
{
	char reference[10];
	int delay;
	sscanf(msg, "%*d %s %d", reference, &delay);
	sprites.SetFrameDelay(reference, delay);
}

void Framework::SetAnimation(char *msg)
{
	char reference[10];
	int animate;
	sscanf(msg, "%*d %s %d", reference, &animate);
	sprites.SetAnimation(reference, animate);
}

void Framework::SetFrame(char *msg)
{
	char reference[10];
	int frame;
	sscanf(msg, "%*d %s %d", reference, &frame);
	printf("Getting frame for %s\n", reference);
	sprites.SetFrame(reference, frame);
}

void Framework::MoveSprite(char *msg)
{
	char reference[10];
	int x, y, speed;
	sscanf(msg, "%*d %s %d %d %d", reference, &x, &y, &speed);
	sprites.MoveSprite(reference, x+XOFFSET, y, speed);
}

void Framework::SetTextPosition(char *msg)
{
	char reference[10];
	int x, y;
	sscanf(msg, "%*d %s %d %d", reference, &x, &y);
	textObjects.SetTextPosition(reference, x, y);
}

void Framework::SetTextSize(char *msg)
{
	char reference[10];
	int size;
	sscanf(msg, "%*d %s %d", reference, &size);
	textObjects.SetSize(reference, size);
}

void Framework::SetTextColor(char *msg)
{
	char reference[10];
	int r, g, b;
	sscanf(msg, "%*d %s %d %d %d", reference, &r, &g, &b);
	textObjects.SetColor(reference, r, g, b);
}

void Framework::SetTextBackgroundColor(char *msg)
{
	char reference[10];
	int r, g, b;
	sscanf(msg, "%*d %s %d %d %d", reference, &r, &g, &b);
	textObjects.SetBackgroundColor(reference, r, g, b);
}

void Framework::ShowText(char *msg)
{
	char reference[10];
	int show;
	sscanf(msg, "%*d %s %d", reference, &show);
	textObjects.ShowText(reference, show, buffer);
}

void Framework::PlayFile(char *msg)
{
	char reference[10];
	sscanf(msg, "%*d %s", reference);
	audioObjects.PlaySample(reference, options.VOLUME); // EDIT volume
}


void Framework::ResetLoop(char *msg)
{
	char reference[10];
	int loop;
	sscanf(msg, "%*d %s %d", reference, &loop);
	audioObjects.ResetLoopFlag(reference, loop);
}

void Framework::StopFile(char *msg)
{
	char reference[10];
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
	//sendMessage(mouse_message.c_str());
	GameFramework::mouseMessage(mouse_message.c_str());
	message.clear();
	message.str("");
	mouse_message.clear();
	if(mouse.StateChange(button, state, x, y))
	{
		std::string sprite_name = sprites.CheckClicks(mouse.GetPointer());
		if(x >= 0 && x <= 600 && y >= 0 && y <= 600/* && gameRunning*/) // Game event
		{
			cout << "Click at ("<< x << "," << y << ")." << endl;
			message.clear();
			message.str("");
			message << "102 " << button << " " << state << " " << x << " " << y << endl;
			mouse_message = message.str();
			//sendMessage(mouse_message.c_str());
			GameFramework::mouseMessage(mouse_message.c_str());
			message.clear();
			mouse_message.clear();
			if(strcmp(sprite_name.c_str(), "") != 0)
			{				
				message.clear();
				message.str("");
				message << "103 " << button << " " << state << " " << sprite_name.c_str() << endl;
				mouse_message = message.str();
				//sendMessage(mouse_message.c_str());
				GameFramework::mouseMessage(mouse_message.c_str());
				message.clear();
				mouse_message.clear();
			}
		}
		else // Framework event
		{
			x += XOFFSET; // Reset x to reflect entire screen instead of only the game window
			std::string sprite_name = sprites.CheckClicks(mouse.GetPointer());
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
		message << "201 " << key << " " << state << endl;
		key_message = message.str();
		//sendMessage(key_message.c_str());
		GameFramework::kybdMessage(key_message.c_str());
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

 
void Framework::CreateGameProcess(std::wstring szCmdline)
// Create a child process that uses the previously created pipes for STDIN and STDOUT.
{ 
	
   STARTUPINFO siStartInfo;
   BOOL bSuccess = FALSE; 
 
// Set up members of the PROCESS_INFORMATION structure. 
 
	   ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
 
// Set up members of the STARTUPINFO structure. 
// This structure specifies the STDIN and STDOUT handles for redirection.
 
	ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO); 
	siStartInfo.hStdOutput = hStdOut_Child;
	siStartInfo.hStdInput = hStdIn_Child;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	// set the window display to HIDE
	//if(!DEBUG)
	siStartInfo.wShowWindow = SW_HIDE;

// Create the child process. 

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
   
   // If an error occurs, exit the application. 
	if ( ! bSuccess ) 
	{
		//LPWSTR cTemp = new WCHAR[100];
		//memset(cTemp, 0, 100);
		DWORD dTemp = GetLastError();
		//FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dTemp, 0, cTemp, 100, NULL);
		std::string appPath(szCmdline.begin(), szCmdline.end());
		allegro_message("Game Launch failed. Could not launch %s\n", appPath.c_str());
		//MessageBox(NULL, cTemp, NULL, MB_OK);
		active = false;
	}
	else 
	{
		// Close handles to the child process and its primary thread.
		// Some applications might keep these handles to monitor the status
		// of the child process, for example. 

		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);

		// Set game running flag
		gameRunning = true;
	}
}


void Framework::CreateTextFromRef(char *msg)
{
	int x, y;
	std::string refName, assetName;
	sscanf(msg, "%*d %s %d %d %s", refName, &x, &y, assetName);
	textObjects.AddTextByRef(refName, assetName, x, y, true);
}

void Framework::CreateTextFromString(char *msg)
{
	char c;
	char *currStr = "";
	int code, x, y, length;
	std::string refName;
	//sscanf(msg, "%*d %s %d %d %d", refName, &x, &y);
	std::stringstream stream;
	stream << msg; // put msg into stream
	stream >> code >> refName >> length >> x >> y;	

	// get code
	stream.get(c);
	//for(int i = 0; i < 4; i++)
	//{
	//	while(c != ' ')
	//	{
	//		stream.get(c);
	//	}
	//	stream.get(c);
	//}

	char *string = new char[length+1];

	stream.getline(string, length+1);
	textObjects.AddText(refName, string, x, y, true);
}

void Framework::RemoveText(char *msg)
{
	std::string refName;
	sscanf(msg, "%*d %s", refName);
}

void Framework::ChangeText(char *msg)
{	
	char c;
	char *currStr = "";
	int code, length;
	std::string refName;
	std::stringstream stream;
	stream << msg; // put msg into stream
	stream >> code >> refName >> length;	

	stream.get(c); // Get space

	char *string = new char[length+1];

	stream.getline(string, length+1);
	textObjects.ChangeText(refName, string);
}


void Framework::LoadGameAssets(int gameIndex)
{
	std::string gamePath = "";
	std::string imageFilePath = games[gameIndex].imageFile;
	std::string audioFilePath = games[gameIndex].audioFile;
	std::string textFilePath = games[gameIndex].textFile;

	LoadImages(imageFilePath, gamePath);
	LoadAudio(audioFilePath, gamePath);
	LoadText(textFilePath, gamePath);
}


void Framework::LoadImages(std::string file_name, std::string gamePath)
{
	std::string file = gamePath + file_name;
	std::wstring w_file(file.begin(), file.end());
	if(imgXML.Load(w_file.c_str()))
		LoadGameImages(gamePath);
	else
	{
		allegro_message("Image asset XML file not found at %s.", file.c_str());
		active = false;
	}
}

void Framework::LoadAudio(std::string file_name, std::string gamePath)
{
	std::string file = gamePath + file_name;
	std::wstring w_file(file.begin(), file.end());
	if(audXML.Load(w_file.c_str()))
		LoadGameAudio(gamePath);
	else
	{
		file_name.erase(0, 8);
		allegro_message("Audio asset XML file not found at %s.", file.c_str());
		active = false;
	}
}

void Framework::LoadText(std::string file_name, std::string gamePath)
{
	std::string file = gamePath + file_name;
	std::wstring w_file(file.begin(), file.end());
	if(txtXML.Load(w_file.c_str()))
		LoadGameText(gamePath);
	else
	{
		file_name.erase(0, 8);
		allegro_message("Text asset XML file not found at %s.", file.c_str());
		active = false;
	}
}


void Framework::LoadGameImages(std::string gamePath)
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
		std::wstring atWidth = imgXML.GetAttrib(TEXT("spriteWidth"));
		std::wstring atHeight = imgXML.GetAttrib(TEXT("spriteHeight"));
		// Set variables for attributes
		std::string file(atFile.begin(), atFile.end());
		file = gamePath + file;
		std::string ref(atRef.begin(), atRef.end());
		std::string numFrames(atNumFrames.begin(), atNumFrames.end());
		std::string numFrameCol(atNumFrameCol.begin(), atNumFrameCol.end());
		std::string width(atWidth.begin(), atWidth.end());
		std::string height(atHeight.begin(), atHeight.end());
		imgXML.OutOfElem();
		
		// Add file to sprite handler
		bool ret = sprites.AddFile(ref, file, atoi(numFrames.c_str()), atoi(numFrameCol.c_str()), atoi(width.c_str()), atoi(height.c_str()));
		if(!ret)
			allegro_message("%s not loaded.", file.c_str());

	}
}

void Framework::LoadGameAudio(std::string gamePath)
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
		file = gamePath + file;
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
			active = false;
			return;
		}

		temp = load_sample(file.c_str());
		if(!temp)
		{
			allegro_message("File not found at \"%s\". Audio Sample \"%s\" not added.", file.c_str(), ref.c_str());
			active = false;
		}
		else
			audioObjects.AddSample(ref, temp, loopVal);
	}
	destroy_sample(temp);
}

void Framework::LoadGameText(std::string gamePath)
{
	txtXML.FindElem();
	int x, y;
	bool visVal = false;
	while(txtXML.FindChildElem(TEXT("text")))
	{
		x=0; y=0;
		txtXML.IntoElem();
		// Get attributes
		std::wstring atString = txtXML.GetAttrib(TEXT("std::string"));
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
			allegro_message("Error in Text XML file (visible value).");
			active = false;
			return;
		}

		textObjects.AddText(ref, textString, x, y, visVal);
	}
}

void Framework::clearBuffer()
{ memset(incMessage, 0, MAX_MESSAGE_SIZE); }

void Framework::ParseMessage(std::stringstream &msgStream)
{
	char message[MAX_MESSAGE_SIZE];
	int code;
	//cout << "Inc Message : " <<  msgStream.str() << endl;
	while(!msgStream.eof())
	{
		memset(message, 0, MAX_MESSAGE_SIZE);
		msgStream.getline(message, MAX_MESSAGE_SIZE);
		code = 0;
		sscanf(message, "%d", &code);
		if(!code)
		{ 
			if(strlen(message)) 
				printf("Debug Message : %s\n", message); 
			continue; 
		}
		//printf("%s\n", message);
		//switch(code)
		//{
		//	// Sprites
		//case SPRITE_CREATE : CreateSprite(message); break;
		//case SPRITE_CREATE_FROM_ASSET : CreateSpriteRefDimensions(message); break;
		//case SPRITE_REMOVE : KillSprite(message); break;
		//case SPRITE_VISIBILITY_CHANGE : ShowSprite(message); break;
		//case SPRITE_SET_SIZE : SetSpriteSize(message); break;
		//case SPRITE_SET_LOCATION : SetSpriteLocation(message); break;
		//case SPRITE_SET_FRAME_DELAY : SetFrameDelay(message); break;
		//case SPRITE_SET_ANIMATION : SetAnimation(message); break;
		//case SPRITE_SET_FRAME : SetFrame(message); break;
		//case SPRITE_MOVE_TO : MoveSprite(message); break;
		//case SPRITE_CHANGE_BITMAP : ChangeBitmap(message); break;
		//	// Text
		//case TEXT_CREATE_FROM_ASSET	: CreateTextFromRef(message); break;
		//case TEXT_CREATE_FROM_STRING : CreateTextFromString(message); break; 
		//case TEXT_REMOVE : RemoveText(message); break;
		//case TEXT_CHANGE_CONTENT : ChangeText(message); break;
		//case TEXT_CHANGE_LOCATION : SetTextPosition(message); break;
		//case TEXT_VISIBILITY_CHANGE : ShowText(message); break;
		//case TEXT_SIZE_CHANGE : SetTextSize(message); break;
		//case TEXT_COLOR_CHANGE : SetTextColor(message); break;
		//case TEXT_BGCOLOR_CHANGE : SetTextBackgroundColor(message); break;
		//	// Audio
		//case AUDIO_PLAY	: PlayFile(message); break;		 
		//case AUDIO_SET_LOOP_COUNT : ResetLoop(message); break;
		//case AUDIO_STOP	: StopFile(message); break;
		//	// Score
		//case SCORE : PostScore(message); break;
		//default :  printf("Debug Message : %s\n", message); 
		//	break;
		//}
	}
}

void Framework::ChangeBitmap(char* msg)
{
	char refName[5], fileRef[25];
	sscanf(msg, "%*d %s %s", refName, fileRef);
	sprites.ChangeBitmap(refName, fileRef);
}


void Framework::KillModule()
{
	if(gameRunning)
	{
		gameRunning = false;
		menuRunning = true;
		// Kill game
		// Launch menu
	}
	else if(menuRunning)
	{
		menuRunning = false; // Kill menu
		active = false; // Exit framework
	}
	DWORD access = PROCESS_ALL_ACCESS;
	HANDLE pHandle = OpenProcess(access, false, piProcInfo.dwProcessId);
	TerminateProcess(pHandle, 0);
	CloseHandle(pHandle);
	CloseHandle(hStdIn_Parent);
	CloseHandle(hStdOut_Parent);
	CloseHandle(hStdIn_Child);
	CloseHandle(hStdOut_Child);
}

void Framework::SetSpriteVisible(char *msg)
{
	char refName[5];
	int visible;
	sscanf(msg, "%*d %s %d", refName, &visible);
	sprites.SetVisible(refName, visible);	
}

void Framework::SetTextVisible(char *msg)
{
	char refName[5];
	int visible;
	sscanf(msg, "%*d %s %d", refName, &visible);
	textObjects.SetVisible(refName, visible);
}