#include "engine.h"
#include "../api_code/GameFramework.h"

// Set inst to NULL to begin
Framework* Framework::inst = NULL;
Game Framework::games[MAXGAMES];
int Framework::gameCount = 0;

/******************************************************
	Provides a pointer to the Singleton instance of the
	Framework class. If there is not an instance, it calls
	the constructor.

	@param user The username that the score of the game 
			will be posted for.
	@return A pointer to the single Framework instance.
******************************************************/
Framework* Framework::Instance(std::string user)
{
	if(!inst)
	{
		inst = new Framework(user);
		// Hide console window
		HWND hWnd = GetConsoleWindow();
		if(hWnd)
		  ShowWindow(hWnd, SW_HIDE);
	}
	return inst;
}

/******************************************************
	Default constructor.
******************************************************/
Framework::Framework()
{
	gameRunning = false;
	username = "Anonymous";
	active = true;
	gameCount = 0;
	options.VOLUME = 50;
	options.MUTE = false;
	options.TTS = false;
	menuRunning = true;
}

/******************************************************
	Protected constructor

	@param user The username that the score of the game 
			will be posted for.
******************************************************/
Framework::Framework(std::string user)
{
	gameRunning = false;
	username = user;
	active = true;
	gameCount = 0;
	options.VOLUME = 50;
	options.MUTE = false;
	options.TTS = false;
	if(GAMENUM != -1) // If this is a game and not the main menu
					  // load the side menu
		LoadSideMenu();
	LoadGames();
	menuRunning = true;
	if(GAMENUM != -1)
		LaunchGame(GAMENUM);
	buffer = create_bitmap(800, 600);
}

/******************************************************
	Default destructor. Destroys all pointers used by
	Allegro.
******************************************************/
Framework::~Framework()
{
	show_mouse(NULL);
	destroy_bitmap(buffer);
	active = false;
	inst = NULL;
}

/******************************************************
	Clears the current screen and calls the sprite handler's
	draw method.
******************************************************/
void Framework::UpdateSprites()
{
	clear_to_color(buffer, makecol(255, 255, 255));
	sprites.DrawSprites(buffer);

	// Draw mouse pointer
	if(mouse_x >= 0 && mouse_x <= 800 && mouse_y >= 0 && mouse_y <= 600)
		draw_sprite(buffer, mouse_sprite, mouse_x, mouse_y);
}

/******************************************************
	Calls the text handler's draw method to show all text
	objects that are visible and reads all visible and
	invisible text.
******************************************************/
void Framework::UpdateText()
{
	textObjects.ShowAllVisible(buffer);
}

/******************************************************
	The Framework's main method calls for each iteration.
******************************************************/
bool Framework::MessageLoop(bool pause)
{
	if(key[KEY_ESC] || !active)
	{
		//Kill Program
		active = false;
	}

	UpdateSprites();
	UpdateText();
	UpdateMouse();
	UpdateKeyboard();
	UpdateOptions(pause);
	//if(gameRunning)
	//{
		//GetMessages();		
	//}
	//CheckErrors();
	return active;
}

/******************************************************
	The Framework's public method to provide iterative
	calls to its main loop method.
******************************************************/
bool Framework::MainLoop(bool pause)
{	
	if(pause) return true;
	// Process normally if not paused
	bool retVal = MessageLoop(pause);	
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, 800, 600);
	release_screen();
	return retVal;
	
}

/******************************************************
	Creates anonymous pipes via the operating system
	by which modules and the framework will communicate.
	This is not currently being used.
******************************************************/
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

/******************************************************
	Launches the game at the given index. If the framework
	and modules become separate EXE files, this will be used
	to create the message pipes and create the module's process.

	@param gameNum A zero-based index value that represents
				   a game's information's relative position
				   in the Games.XML file.
******************************************************/
void Framework::LaunchGame(int gameNum)
{
	LoadGameAssets(gameNum);
	//CreateMessagePipes();
	//std::string gameExe = "modules/"+games[gameNum].path + games[gameNum].name + ".exe";
	//std::wstring gameToLaunch(gameExe.begin(), gameExe.end());
	//TCHAR szCmdline[]=TEXT("modules\\Wordplay\\Wordplay.exe");
	//CreateGameProcess(gameToLaunch);
}

/******************************************************
	Loads the information for all the games specified in
	the Games.XML file and stores the information in a
	game struct.
******************************************************/
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
		if(strcmp(iconPath.c_str(), "Default") != 0)
		{
			games[gameCount].icon.path = iconPath;
			games[gameCount].icon.width = atoi(iconWidth.c_str());
			games[gameCount].icon.height = atoi(iconHeight.c_str());
		}
		else
		{
			games[gameCount].icon.path = "data/images/default_icon.bmp";
			games[gameCount].icon.width = 100;
			games[gameCount].icon.height = 100;
		}
		gameCount++;
	}
	// This is needed to load the game icons in the case
	// that this program is the main menu responsible for
	// launching the game modules.
	if(GAMENUM == -1) 
		LoadMenuImages();
}

/******************************************************
	Reads the inbound pipe to receive messages from the
	currently active module.
******************************************************/
void Framework::GetMessages()
{
	DWORD bytesRead, bytesAvail;
	std::stringstream msgStream;
	msgStream.clear();
	PeekNamedPipe(hStdIn_Parent, incMessage, MAX_MESSAGE_SIZE, &bytesRead, &bytesAvail, NULL);
	if (bytesRead != 0)
	{
		clearBuffer();
		if (bytesAvail > MAX_MESSAGE_SIZE)
		{
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

/******************************************************
	Adds a message to the outbound pipe for retrieval
	by the currently active module.

	@param msg The message to be sent to the module.
******************************************************/
void Framework::sendMessage(const char *msg)
{
	DWORD bytesWritten;
	std::string message(msg);
	WriteFile(hStdOut_Parent, message.c_str(), message.size(), &bytesWritten, NULL);
}

/******************************************************
	Adds a new sprite object to the sprite handler based
	on information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::CreateSprite(char *msg)
{
	int x, y, w, h;
	char reference[25], imageReference[25];
	sscanf(msg, "%*d %s %s %d %d %d %d", reference, imageReference, &x, &y, &w, &h);
	std::string str_reference = reference;
	std::string str_imageReference = imageReference;
	sprites.AddSprite(str_reference, str_imageReference, x+XOFFSET, y, w, h);
}

/******************************************************
	Adds a new sprite object to the sprite handler based
	on information received via a message from the module.
	This message does not contain width or height information.
	The sprite's width and height will be based on the associated
	bitmap file's loaded dimensions.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework:: CreateSpriteRefDimensions(char *msg)
{
	int x, y;
	char reference[25], imageReference[25];
	sscanf(msg, "%*d %s %s %d %d", reference, imageReference, &x, &y);
	std::string str_reference = reference;
	std::string str_imageReference = imageReference;
	sprites.AddSprite(str_reference, str_imageReference, x+XOFFSET, y);
}


/******************************************************
	Removes a specified sprite object from the sprite handler based
	on information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::KillSprite(char *msg)
{
	char reference[10];
	sscanf(msg, "%*d %s", reference);
	std::string str_reference = reference;
	if(!sprites.RemoveSprite(str_reference))
		allegro_message("Sprite %s could not be removed", str_reference.c_str());
}

/******************************************************
	Changes the visibility of an active sprite object based
	on information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::SetSpriteVisible(char *msg)
{
	char refName[5];
	int visible;
	sscanf(msg, "%*d %s %d", refName, &visible);
	sprites.SetVisible(refName, visible);	
	UpdateSprites();
}

/******************************************************
	Changes the size of a sprite in the sprite handler based
	on information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::SetSpriteSize(char *msg)
{
	char reference[10];
	int w, h;
	sscanf(msg, "%*d %s %d %d", reference, &w, &h);
	sprites.SetSpriteSize(reference, w, h);
}

/******************************************************
	Changes the screen location of a sprite in the sprite handler based
	on information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::SetSpriteLocation(char *msg)
{
	char reference[10];
	int x, y;
	sscanf(msg, "%*d %s %d %d", reference, &x, &y);
	printf("Setting location for %s at %d , %d\n", reference, x, y);
	sprites.SetSpriteLocation(reference, x+XOFFSET, y);
}

/******************************************************
	Changes the animation frame delay of a sprite in the sprite handler based
	on information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::SetFrameDelay(char *msg)
{
	char reference[10];
	int delay;
	sscanf(msg, "%*d %s %d", reference, &delay);
	sprites.SetFrameDelay(reference, delay);
}

/******************************************************
	Changes whether or not a sprite should be animated based
	on information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::SetAnimation(char *msg)
{
	char reference[10];
	int animate;
	sscanf(msg, "%*d %s %d", reference, &animate);
	sprites.SetAnimation(reference, animate);
}

/******************************************************
	Changes the current animation frame of a sprite in the sprite handler based
	on information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::SetFrame(char *msg)
{
	char reference[10];
	int frame;
	sscanf(msg, "%*d %s %d", reference, &frame);
	printf("Getting frame for %s\n", reference);
	sprites.SetFrame(reference, frame);
}

/******************************************************
	Moves a sprite to a new screen location based
	on information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::MoveSprite(char *msg)
{
	char reference[10];
	int x, y, speed;
	sscanf(msg, "%*d %s %d %d %d", reference, &x, &y, &speed);
	sprites.MoveSprite(reference, x+XOFFSET, y, speed);
}

/******************************************************
	Changes the associated bitmap file for a sprite
	based on information received via a message from the
	module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::ChangeBitmap(char* msg)
{
	char refName[5], fileRef[25];
	sscanf(msg, "%*d %s %s", refName, fileRef);
	sprites.ChangeBitmap(refName, fileRef);
}

/******************************************************
	Changes the screen location of a text object based
	on information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::SetTextPosition(char *msg)
{
	char reference[10];
	int x, y;
	sscanf(msg, "%*d %s %d %d", reference, &x, &y);
	textObjects.SetTextPosition(reference, x, y);
}

/******************************************************
	Changes the size of a text object based
	on information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::SetTextSize(char *msg)
{
	char reference[10];
	int size;
	sscanf(msg, "%*d %s %d", reference, &size);
	textObjects.SetSize(reference, size);
}

/******************************************************
	Changes the foreground color of a text object based
	on information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::SetTextColor(char *msg)
{
	char reference[10];
	int r, g, b;
	sscanf(msg, "%*d %s %d %d %d", reference, &r, &g, &b);
	textObjects.SetColor(reference, r, g, b);
}

/******************************************************
	Changes the background color of a text object based
	on information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::SetTextBackgroundColor(char *msg)
{
	char reference[10];
	int r, g, b;
	sscanf(msg, "%*d %s %d %d %d", reference, &r, &g, &b);
	textObjects.SetBackgroundColor(reference, r, g, b);
}

/******************************************************
	Changes the visibility of an active text object based
	on information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::SetTextVisible(char *msg)
{
	char refName[5];
	int visible;
	sscanf(msg, "%*d %s %d", refName, &visible);
	textObjects.SetVisible(refName, visible);
}


/******************************************************
	Creates a new text object from a text asset reference in the
	XML file based on information received via a message from the
	module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::CreateTextFromRef(char *msg)
{
	int x, y;
	std::string refName, assetName;
	sscanf(msg, "%*d %s %d %d %s", refName, &x, &y, assetName);
	textObjects.AddTextByRef(refName, assetName, x, y, true);
}

/******************************************************
	Creates a new text object for a given text string
	based on information received via a message from the
	module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
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

	// get hanging space
	stream.get(c);

	char *string = new char[length+1];
	// remainder of the stream is the string
	stream.getline(string, length+1);
	textObjects.AddText(refName, string, x, y, true);
}

/******************************************************
	Removes a text object from the text handler
	based on information received via a message from the
	module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::RemoveText(char *msg)
{
	std::string refName;
	sscanf(msg, "%*d %s", refName);
}

/******************************************************
	Changes the string of a text object
	based on information received via a message from the
	module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::ChangeText(char *msg)
{	
	char c;
	char *currStr = "";
	int code, length;
	std::string refName;
	std::stringstream stream;
	stream << msg; // put msg into stream
	stream >> code >> refName >> length;	

	stream.get(c); // Get hanging space

	char *string = new char[length+1];

	stream.getline(string, length+1);
	textObjects.ChangeText(refName, string);
}

/******************************************************
	Reads a string of text without displaying it to the
	screen. This does not create a text object.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::ReadText(char *msg)
{	
	// only do if text-to-speech is enabled
	// and sound is not muted
	if(!options.TTS && !options.MUTE) return;
	
	char c;
	int code, length;
	std::stringstream stream;
	stream << msg; // put msg into stream
	stream >> code >> length;	

	stream.get(c); // Get hanging space

	char *string = new char[length+1];

	stream.getline(string, length+1);
	std::string stringToRead = string;
		Text::ReadText(stringToRead, options.VOLUME);
}

/******************************************************
	Creates an audio object reference for use by the API to
	stop and play audio files.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::CreateAudioObject(char *msg)
{
	char reference[10], assetName[50];
	sscanf(msg, "%*d %s %s", reference, assetName);
	audioObjects.MapSample(reference, assetName); // EDIT volume
}

/******************************************************
	Plays a loaded audio file specified by information received 
	via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::PlayFile(char *msg)
{
	char reference[10];
	sscanf(msg, "%*d %s", reference);
	audioObjects.PlaySample(reference, options.VOLUME); // EDIT volume
}

/******************************************************
	Updates the loop variable of a loaded audio file specified 
	by information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::ResetLoop(char *msg)
{
	char reference[10];
	int loop;
	sscanf(msg, "%*d %s %d", reference, &loop);
	audioObjects.ResetLoopFlag(reference, loop);
}

/******************************************************
	Stops a loaded audio file specified by information received 
	via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::StopFile(char *msg)
{
	char reference[10];
	sscanf(msg, "%*d %s", reference);
	audioObjects.StopSample(reference);
}

/******************************************************
	Posts the players score upon exiting the game based on
	information received via a message from the module.

	@param msg The message that has been received from the module
				containing information needed for the function call.
******************************************************/
void Framework::PostScore(char *msg)
{
	int score;
	sscanf(msg, "%*d %d", &score);
	gameRunning = false;
}

/******************************************************
	Handles the sending of mouse events and location changes
	to the module as well as Framework-only events (i.e. side menu
	interaction).
******************************************************/
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
			x += XOFFSET; // Reset mouse's x position to reflect entire screen 
						  // instead of only the game window
			std::string sprite_name = sprites.CheckClicks(mouse.GetPointer());
			if(button == 1 && state == 1 && strcmp(sprite_name.c_str(), "") != 0) // see if a sprite is clicked
			{
				// change Text-to-Speech boolean value
				if(strcmp(sprite_name.c_str(), "tts_box") == 0
					|| strcmp(sprite_name.c_str(), "tts_banner") == 0)
				{
					options.TTS ^= true;
					sprites.SetFrame("tts_box", options.TTS);
				}
				// change mute boolean value
				if(strcmp(sprite_name.c_str(), "mute_box") == 0
					|| strcmp(sprite_name.c_str(), "mute_banner") == 0)
				{
					options.MUTE ^= true;
					sprites.SetFrame("mute_box", options.MUTE); // checked
				}
				// adjust volume
				if(strcmp(sprite_name.c_str(), "vol_bar") == 0
					|| strcmp(sprite_name.c_str(), "vol_pointer") == 0)
				{
					x -= 3;
					if(x < 42) x = 42;
					if(x > 150) x = 150;
					sprites.SetSpriteLocation("vol_pointer", x, 465);
					options.VOLUME = ((x - 45) * 100) / 110.0;
				}
			}
		}
	}
}

/******************************************************
	Handles the sending of keyboard events and to the module 
	as well as Framework-only events (i.e. side menu interaction).
******************************************************/
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

/******************************************************
	Returns the state (running or not running) of the Framework.

	@return true if the Framework loop is still running, false otherwise
******************************************************/
bool Framework::isActive()
{ 
	return active;
}

/******************************************************
	Returns the state (running or not running) of modules.

	@return true if a module is running, false otherwise
******************************************************/
bool Framework::gameIsRunning() 
{ 
	return gameRunning; 
}

/******************************************************
	Handles the passing of the current desire Text-to-Speech 
	option and volume states to the objects that need them
	(text handler and audio handler).
******************************************************/
void Framework::UpdateOptions(bool pause)
{	
	if(options.VOLUME < 0) options.VOLUME = 0;
	if(options.VOLUME > 100) options.VOLUME = 100;
	if(options.MUTE || pause)
		audioObjects.Mute();
	else
		audioObjects.Unmute();
	audioObjects.SetVolume(options.VOLUME);
	textObjects.SetTTS(options.TTS);
}

 
/******************************************************
	Creates a new operating system process to run a game
	module's program. This is not currently in use but is
	available if separation between the modules and Framework
	is desired.

	@param szCmdline The command line string specifying the
				     module's EXE location and any command line
					 options.
******************************************************/
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

/******************************************************
	Loads the image, audio, and text assets specified in
	a module's XML files.

	@param gameNum The zero-based index into the games array.
					This also represents a game's information's
					relative location in the Games.XML file.
******************************************************/
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

/******************************************************
	Loads the image assets from an XML file at the specified
	path and file name.

	@param file_name The path to the XML file relative to the
					 module's EXE location.
    @param gamePath The path to the module's EXE location relative
					to the Framework's location.
******************************************************/
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

/******************************************************
	Loads the audio assets from an XML file at the specified
	path and file name.

	@param file_name The path to the XML file relative to the
					 module's EXE location.
    @param gamePath The path to the module's EXE location relative
					to the Framework's location.
******************************************************/
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

/******************************************************
	Loads the text assets from an XML file at the specified
	path and file name.

	@param file_name The path to the XML file relative to the
					 module's EXE location.
    @param gamePath The path to the module's EXE location relative
					to the Framework's location.
******************************************************/
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

/******************************************************
	Loads the image asset files that are currently specified
	in the loaded imgXML variable.

	@param gamePath The path relative to the Framework's EXE
					needed to concatenate module relative
					asset paths onto.
******************************************************/
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

/******************************************************
	Loads the audio asset files that are currently specified
	in the loaded audXML variable.

	@param gamePath The path relative to the Framework's EXE
					needed to concatenate module relative
					asset paths onto.
******************************************************/
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
}

/******************************************************
	Loads the text asset files that are currently specified
	in the loaded txtXML variable.

	@param gamePath The path relative to the Framework's EXE
					needed to concatenate module relative
					asset paths onto.
******************************************************/
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

/******************************************************
	Stops the module's process and closes the anonymous
	pipes.
******************************************************/
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

/******************************************************
	Clears the incoming/outgoing message buffer by setting
	the all values in the buffer to zero.
******************************************************/
void Framework::clearBuffer()
{ memset(incMessage, 0, MAX_MESSAGE_SIZE); }

/******************************************************
	Parses an incoming message stream. Determines the code
	of the incoming message and calls the related function.

	@param msgStream The incoming message string stream being
				     parsed for some number of distinct messages.
******************************************************/
void Framework::ParseMessage(std::stringstream &msgStream)
{
	char message[MAX_MESSAGE_SIZE];
	int code;

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

		switch(code)
		{
			// Sprites
		case SPRITE_CREATE : CreateSprite(message); break;
		case SPRITE_CREATE_FROM_ASSET : CreateSpriteRefDimensions(message); break;
		case SPRITE_REMOVE : KillSprite(message); break;
		case SPRITE_VISIBILITY_CHANGE : SetSpriteVisible(message); break;
		case SPRITE_SET_SIZE : SetSpriteSize(message); break;
		case SPRITE_SET_LOCATION : SetSpriteLocation(message); break;
		case SPRITE_SET_FRAME_DELAY : SetFrameDelay(message); break;
		case SPRITE_SET_ANIMATION : SetAnimation(message); break;
		case SPRITE_SET_FRAME : SetFrame(message); break;
		case SPRITE_MOVE_TO : MoveSprite(message); break;
		case SPRITE_CHANGE_BITMAP : ChangeBitmap(message); break;
			// Text
		case TEXT_CREATE_FROM_ASSET	: CreateTextFromRef(message); break;
		case TEXT_CREATE_FROM_STRING : CreateTextFromString(message); break; 
		case TEXT_REMOVE : RemoveText(message); break;
		case TEXT_CHANGE_CONTENT : ChangeText(message); break;
		case TEXT_CHANGE_LOCATION : SetTextPosition(message); break;
		case TEXT_VISIBILITY_CHANGE : SetTextVisible(message); break;
		case TEXT_SIZE_CHANGE : SetTextSize(message); break;
		case TEXT_COLOR_CHANGE : SetTextColor(message); break;
		case TEXT_BGCOLOR_CHANGE : SetTextBackgroundColor(message); break;
		case TEXT_READ : ReadText(message); break;
			// Audio
		case AUDIO_CREATE : CreateAudioObject(message);
		case AUDIO_PLAY	: PlayFile(message); break;		 
		case AUDIO_SET_LOOP_COUNT : ResetLoop(message); break;
		case AUDIO_STOP	: StopFile(message); break;
			// Score
		case POST_SCORE : PostScore(message); break;
		default :  printf("Debug Message : %s\n", message); 
			break;
		}
	}
}

/******************************************************
	Loads and displays the sprites for the side menu to
	allow changing the volume and text-to-speech on/off
	setting.
******************************************************/
void Framework::LoadSideMenu()
{
	int w = 0, h = 0;
	// Load the side menu sprite files
	sprites.AddFile("CheckBox", "data/images/CheckBox.bmp", 2, 2, 40, 40);
	sprites.AddFile("TTSBanner", "data/images/TTSBanner.bmp", 1, 1, 140, 30);
	sprites.AddFile("VolumeBar", "data/images/VolumeBar.bmp", 1, 1, 110, 30);
	sprites.AddFile("VolumePointer", "data/images/VolumePointer.bmp", 1, 1, 7, 44);
	sprites.AddFile("VolumeBanner", "data/images/VolumeBanner.bmp", 1, 1, 110, 30);
	sprites.AddFile("MuteBanner", "data/images/MuteBanner.bmp", 1, 1, 70, 30);
	// Create the side menu sprites
	sprites.AddSprite("tts_box", "CheckBox", 5, 70);
	sprites.AddSprite("tts_banner", "TTSBanner", 55, 75);
	sprites.AddSprite("vol_bar", "VolumeBar", 45, 465);
	sprites.AddSprite("vol_pointer", "VolumePointer", 97, 465);
	sprites.AddSprite("vol_banner", "VolumeBanner", 45, 520);
	sprites.AddSprite("mute_banner", "MuteBanner", 75, 253);
	sprites.AddSprite("mute_box", "CheckBox", 35, 250);
	// Display them
	sprites.SetVisible("tts_box", 1);
	sprites.SetVisible("tts_banner", 1);
	sprites.SetVisible("vol_bar", 1);
	sprites.SetVisible("vol_pointer", 1);
	sprites.SetVisible("vol_banner", 1);
	sprites.SetVisible("mute_box", 1);
	sprites.SetVisible("mute_banner", 1);
}


void Framework::LoadMenuImages()
{	
	sprites.AddFile("mainmenu_bkg", "data/images/mainmenu_bkg.bmp", 1, 1, 600, 600);
	sprites.AddFile("leftarrow", "data/images/leftarrow.bmp", 1, 1, 100, 100);
	sprites.AddFile("rightarrow", "data/images/rightarrow.bmp", 1, 1, 100, 100);

	for(int i = 0; i < gameCount; i++)
	{		
		char temp[3];
		itoa(i, temp, 10);
		std::string iconName(temp);
		if(strcmp(games[i].icon.path.c_str(), "") != 0)
		{
			iconName = "gameicon." + iconName;
			if(strcmp(games[i].icon.path.c_str(), "data/images/default_icon.bmp") != 0)
				sprites.AddFile(iconName, games[i].path + games[i].icon.path, 1, 1, games[gameCount].icon.width, games[gameCount].icon.height);
			else
				sprites.AddFile(iconName, games[i].icon.path, 1, 1, games[gameCount].icon.width, games[gameCount].icon.height);
		}
	}
}