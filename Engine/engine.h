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

typedef struct
{
	std::string name;
	std::string path;
	std::string imageFile, audioFile, textFile;
	BITMAP *icon;
}Game;

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
	static Framework* Instance(char*);
	
	/* MAIN GAME LOOP */
	void MainLoop();

	/* MESSAGE LOOP FUNCTION */
	void MessageLoop();

	/* GET FILES FOR ASSETS */
	void LoadImages(std::string file_name);
	void LoadAudio(std::string file_name);
	void LoadText(std::string file_name);
	
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


	
private:
	/* TO PREVENT MULTIPLE FRAMEWORK INSTANCES */
	static Framework* inst;

	/* CLASS VARIABLES */
	CMarkup imgXML, audXML, txtXML;
	BITMAP *buffer;
	bool gameRunning, active;
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
	char outMessage[MAX_MESSAGE_SIZE];
	char incMessage[MAX_MESSAGE_SIZE];

	/* MESSAGE HANDLING */
	CMarkup gameList;
	void CreateMessagePipes();
	void LaunchGame(int gameNum);
	void LaunchGame(std::string appPath);
	void GetMessage();
	void SendMessage(const char *msg);
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

	/* KEYBOARD / MOUSE FUNCTIONS */
	void UpdateMouse();
	void UpdateKeyboard();

	/* FUNCTIONS CALLED VIA MESSAGE */
	void CreateSprite(std::stringstream &stream);
	void CreateSpriteRefDimensions(std::stringstream &stream);
	void KillSprite(std::stringstream &stream);
	void ShowSprite(std::stringstream &stream);
	void SetSpriteSize(std::stringstream &stream);
	void SetSpriteLocation(std::stringstream &stream);
	void SetFrameDelay(std::stringstream &stream);
	void SetAnimation(std::stringstream &stream);
	void SetFrame(std::stringstream &stream);
	void MoveSprite(std::stringstream &stream);

	void SetTextPosition(std::stringstream &stream);
	void ShowText(std::stringstream &stream);

	void PlayFile(std::stringstream &stream);
	void ResetLoop(std::stringstream &stream);
	void StopFile(std::stringstream &stream);

	void PostScore(std::stringstream &stream);
};

#endif