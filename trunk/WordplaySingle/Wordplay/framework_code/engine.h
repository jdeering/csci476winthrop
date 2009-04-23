#ifndef _Framework_H
#define _Framework_H

#include "globals.h"
#include "sprite_handler.h"
#include "audio_handler.h"
#include "text_handler.h"
#include "input.h"
#include "Markup.h"
#include <errno.h>


#define MAX_MESSAGE_SIZE 4096*20

/**********************************
	Struct to hold information for
	game icons used in the main menu.
**********************************/
typedef struct
{
	int width, height;
	std::string path; 
}Icon;

/**********************************
	Struct to hold all information needed
	to load a game's assets when launched.
**********************************/
typedef struct
{
	std::string name;
	std::string path;
	std::string imageFile, audioFile, textFile;
	Icon icon;
}Game;

/**********************************
	Struct to control the volume and
	text-to-speech options.
**********************************/
typedef struct
{
	int VOLUME;
	bool MUTE;
	bool TTS;
}OPTIONS;

class Framework
{
public:
	/* PUBLIC DESTRUCTOR */
	~Framework();

	/* SINGLETON INSTANCE METHOD */
	static Framework* Instance(std::string);
	
	/* MAIN GAME LOOP */
	bool MainLoop(bool);

	/* MESSAGE LOOP FUNCTION */
	bool MessageLoop(bool);

	/* GAMES THAT CAN BE LAUNCHED */
	static Game games[MAXGAMES];
	static int gameCount;

	/* GET FILES FOR GAME ASSETS */
	void LoadImages(std::string file_name, std::string gamePath);
	void LoadAudio(std::string file_name, std::string gamePath);
	void LoadText(std::string file_name, std::string gamePath);
	
	bool isActive();
	bool gameIsRunning();

protected:
	/* PROTECTED CONSTRUCTORS */
	Framework();
	Framework(std::string);
	Framework(const Framework& fw);
	Framework& operator=(const Framework&);

	void clearBuffer();
	
private:
	/* TO PREVENT MULTIPLE FRAMEWORK INSTANCES */
	static Framework* inst;

	/* CLASS VARIABLES */
	CMarkup imgXML, audXML, txtXML;
	BITMAP *buffer;
	bool gameRunning, menuRunning, active;
	OPTIONS options;
	std::string username;

	/* MOUSE AND KEYBOARD HANDLERS */
	Mouse mouse;
	Keyboard keyboard;

	/* MESSAGE HANDLING VARIABLES */
	HANDLE hStdIn_Parent, hStdOut_Parent;
	HANDLE hStdIn_Child, hStdOut_Child;
    PROCESS_INFORMATION piProcInfo; // maintained to close module process
	char incMessage[MAX_MESSAGE_SIZE];

	/* MESSAGE HANDLING */
	CMarkup gameList;
	void CreateGameProcess(std::wstring);
	void KillModule();
	void KillMainMenu();
	void CreateMessagePipes();
	void LaunchGame(int gameNum);
	void GetMessages();
	void sendMessage(const char *msg);
	void ParseMessage(std::stringstream &msgStream);

	/* OBJECT VARIABLES */
	SpriteHandler sprites;
	AudioHandler audioObjects;
	TextHandler textObjects;

	/* UPDATE OBJECTS FUNCTIONS */
	void UpdateSprites();
	void UpdateAudio();
	void UpdateText();
	void UpdateOptions(bool);

	/* OBJECT INITIALIZATION / FILE LOADING */
	void LoadGames();
	void LoadMenuImages();
	void LoadImages();
	void LoadAudio();
	void LoadText();

	void LoadGameAssets(int gameIndex);
	void LoadGameImages(std::string gamePath);
	void LoadGameAudio(std::string gamePath);
	void LoadGameText(std::string gamePath);

	// Loads the side menu sprites
	void LoadSideMenu();

	/* KEYBOARD / MOUSE FUNCTIONS */
	void UpdateMouse();
	void UpdateKeyboard();

public: // Change to private when separating framework from modules
		// i.e. - implementing the pipe method of running modules

	/* FUNCTIONS CALLED VIA MESSAGE */
	// These are called the same way they would be via a pipe,
	// but the pipe implementation is not active
	void CreateSprite(char *msg);
	void CreateSpriteRefDimensions(char *msg);
	void KillSprite(char *msg);
	void SetSpriteSize(char *msg);
	void SetSpriteLocation(char *msg);
	void SetFrameDelay(char *msg);
	void SetAnimation(char *msg);
	void SetFrame(char *msg);
	void MoveSprite(char *msg);
	void ChangeBitmap(char* msg);
	void SetSpriteVisible(char *msg);

	void SetTextPosition(char *msg);
	void CreateTextFromRef(char *msg);
	void CreateTextFromString(char *msg);
	void RemoveText(char *msg);
	void ChangeText(char *msg);
	void SetTextSize(char *msg);
	void SetTextColor(char *msg);
	void SetTextBackgroundColor(char *msg);
	void SetTextVisible(char *msg);
	void ReadText(char *msg);

	void CreateAudioObject(char *msg);
	void PlayFile(char *msg);
	void ResetLoop(char *msg);
	void StopFile(char *msg);

	void PostScore(char *msg);
};

#endif