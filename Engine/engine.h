#ifndef _Framework_H
#define _Framework_H

#include "globals.h"
#include <sstream>
#include "sprite_handler.h"
#include "audio_handler.h"
#include "text_handler.h"
#include "input.h"
#include "Markup.h"

#define MAX_MESSAGE_SIZE 512

class Framework
{
public:
	/* PUBLIC DESTRUCTOR */
	~Framework();

	/* SINGLETON INSTANCE METHOD */
	static Framework* Instance();
	
	/* MAIN GAME LOOP */
	void MainLoop();

	/* MESSAGE LOOP FUNCTION */
	void MessageLoop();

	/* GET FILES FOR ASSETS */
	void LoadImages(std::string file_name);
	void LoadAudio(std::string file_name);
	void LoadText(std::string file_name);
	
	void AddSprite(std::string refName, std::string imageRef, int x, int y, int w, int h)
	{ sprites.AddSprite(refName, imageRef, x, y, w, h); }
	bool isActive() { return active; }
	bool gameIsRunning() { return gameRunning; }
protected:
	/* PROTECTED CONSTRUCTORS */
	Framework();
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
	std::string games[MAXGAMES];

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

	/* OBJECT VARIABLES */
	SpriteHandler sprites;
	AudioHandler audioObjects;
	TextHandler textObjects;

	/* UPDATE OBJECTS FUNCTIONS */
	void UpdateSprites();
	void UpdateAudio();
	void UpdateText();

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
};

#endif