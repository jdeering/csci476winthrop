#ifndef _Framework_H
#define _Framework_H

#include "globals.h"
#include "sprite_handler.h"
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
	
	void AddSprite(int refNum, std::string imageRef, int x, int y, int w, int h)
	{ sprites.AddSprite(refNum, imageRef, x, y, w, h); }
	void MoveSprite(int refNum, int new_x, int new_y, int speed)
	{ sprites.MoveSprite(refNum, new_x, new_y, speed); }
	bool isActive() { return active; }
protected:
	/* PROTECTED CONSTRUCTORS */
	Framework();
	Framework(const Framework& fw);
	Framework& operator=(const Framework&);
	
private:
	/* TO PREVENT MULTIPLE FRAMEWORK INSTANCES */
	static Framework* inst;
	CMarkup imgXML, audXML, txtXML;
	BITMAP *buffer;
	bool active;

	/* MESSAGE HANDLING VARIABLES */
	HANDLE hStdIn, hStdOut;
	char outMessage[MAX_MESSAGE_SIZE];
	char incMessage[MAX_MESSAGE_SIZE];

	/* MESSAGE HANDLING */
	void CreateMessagePipes();
	void LaunchGame(int gameNum);
	void GetMessage();
	void SendMessage(char *msg);

	/* OBJECT VARIABLES */
	SpriteHandler sprites;
//		AudioHandler audioObjects;
//		TextHandler textObjects;

	/* UPDATE OBJECTS FUNCTIONS */
	void UpdateSprites();
	void UpdateAudio();
	void UpdateText();

	/* OBJECT INITIALIZATION / FILE LOADING */
	void LoadImages();
	void LoadAudio();
	void LoadText();

	/* KEYBOARD / MOUSE FUNCTIONS */
	void Mouse();
	void Keyboard();
};

#endif