#ifndef _Framework_H
#define _Framework_H

#include "globals.h"
#include "sprite_handler.h"
#include "audio_handler.h"
#include "text_handler.h"
#include "input.h"
#include "Markup.h"
#include <errno.h>

#define MAX_MESSAGE_SIZE 512

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
	void MainLoop();

	/* MESSAGE LOOP FUNCTION */
	void MessageLoop();

	/* GET FILES FOR MENU ASSETS */
	void LoadImages(std::string file_name);
	void LoadAudio(std::string file_name);
	void LoadText(std::string file_name);

	/* GET FILES FOR GAME ASSETS */
	void LoadImages(std::string file_name, std::string gamePath);
	void LoadAudio(std::string file_name, std::string gamePath);
	void LoadText(std::string file_name, std::string gamePath);
	
	void AddSprite(std::string refName, std::string imageRef, int x, int y, int w, int h);
	bool isActive();
	bool gameIsRunning();
	void DrawMenu();
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
	int gameCount;
	Game games[MAXGAMES];
	OPTIONS options;
	std::string username;

	/* MOUSE AND KEYBOARD HANDLERS */
	Mouse mouse;
	Keyboard keyboard;

	/* MESSAGE HANDLING VARIABLES */
	HANDLE hStdIn_Parent, hStdOut_Parent;
	HANDLE hStdIn_Child, hStdOut_Child;
    PROCESS_INFORMATION piProcInfo; // maintained to close module process
	char outMessage[MAX_MESSAGE_SIZE];
	char incMessage[MAX_MESSAGE_SIZE];

	/* MESSAGE HANDLING */
	CMarkup gameList;
	void CreateGameProcess(std::wstring);
	void KillModule();
	void KillMainMenu();
	void CreateMessagePipes();
	void LaunchGame(int gameNum);
	void LaunchGame(std::string appPath);
	void GetMessages();
	void sendMessage(const char *msg);
	void ParseMessage(std::stringstream &msgStream);
	void CheckErrors();

	/* OBJECT VARIABLES */
	SpriteHandler sprites;
	AudioHandler audioObjects;
	TextHandler textObjects;

	/* UPDATE OBJECTS FUNCTIONS */
	void UpdateSprites();
	void UpdateAudio();
	void UpdateText();
	void UpdateOptions();

	/* OBJECT INITIALIZATION / FILE LOADING */
	void LoadGames();
	void LoadImages();
	void LoadAudio();
	void LoadText();

	void LoadGameAssets(int gameIndex);
	void LoadGameImages(std::string gamePath);
	void LoadGameAudio(std::string gamePath);
	void LoadGameText(std::string gamePath);

	/* KEYBOARD / MOUSE FUNCTIONS */
	void UpdateMouse();
	void UpdateKeyboard();

	/* FUNCTIONS CALLED VIA MESSAGE */
	void CreateSprite(char *msg);
	void CreateSpriteRefDimensions(char *msg);
	void KillSprite(char *msg);
	void ShowSprite(char *msg);
	void SetSpriteSize(char *msg);
	void SetSpriteLocation(char *msg);
	void SetFrameDelay(char *msg);
	void SetAnimation(char *msg);
	void SetFrame(char *msg);
	void MoveSprite(char *msg);
	void ChangeBitmap(char* msg);

	void SetTextPosition(char *msg);
	void ShowText(char *msg);	
	void CreateTextFromRef(char *msg);
	void CreateTextFromString(char *msg);
	void RemoveText(char *msg);
	void ChangeText(char *msg);
	void SetTextSize(char *msg);
	void SetTextColor(char *msg);
	void SetTextBackgroundColor(char *msg);


	void PlayFile(char *msg);
	void ResetLoop(char *msg);
	void StopFile(char *msg);

	void PostScore(char *msg);
};

#endif