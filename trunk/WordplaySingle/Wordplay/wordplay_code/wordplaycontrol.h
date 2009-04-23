/*
Lauren Cairco
13 April 2009
CSCI 476 Project

Wordplaycontrol.h

This static class is for use with the Wordplay game module. It controls the progress of the game play that is not
contained in the Tile, Board, Dictionary, and API classes.

GLOBAL VARIABLES
enum GameStatus {CHOOSE_LEVEL, INSTRUCTIONS_1, INSTRUCTIONS_2, IN_GAME, DIALOGUE_EXIT, DIALOGUE_RESET};
static GameStatus currentState;
	Used to hold the current state of gameplay. Helps keep track of how clicks should be handled.
static GFSprite * background;
	Holds the graphic sprite for the gameplay background.
static Dictionary * userDictionary;
	Holds the dictionary used to compare words to.
static Board * gameBoard;
	Holds the gameboard that users click letters on.
static GFSprite * overlay;
	Points to any fullscreen image that will be shown over top of the gameboard--for example, instructions,
	dialogue boxes, and the select level screen
static GFText * currentWord;
	Text object to display the current word
static GFText * currentScore;
	Text object to display the current score

PUBLIC FUNCTIONS
All these functions are called by the API as defined in the start() function.

static void masterClickHandler(int, int, int, int);
	used to handle clicks inside of gameplay. Passes the coordinates to the appropriate click handler
	for the game state
static bool returnRunning();
	used to determine whether the game should still be running or not
static void start();
	sets up and begins the game

PRIVATE FUNCTIONS
static void introClickHandler(int x, int y)
	handles clicks when in the introduction of the game
static void instructionsClickHandler(int x, int y, int instructionsPage)
	handles clicks when in the instruction screens of the game
static void inGameClickHandler(int x, int y)
	handles clicks when in gameplay
static void gameboardClickHandler(int x, int y)
	handles clicks that are within the gameboard area during gameplay
static void dialogueClickHandler(int x, int y, void (*yesFunction)(), void (*noFunction)())
	handles clicks that are within a dialogue box, using the yes and no functions as parameters for what to do
	if yes and no are clicked

static void showInstructions(int gameLevel, int page)
	shows instructions for the appropriate game level, and page 1 or 2 based on parameter
static void beginGame()
	begins gameplay

static void dialogueBox(string name)
	shows a dialogue box for reset or end, depending on what parameter comes in
static void endDialogue()
	removes the dialogue box and returns back to normal gameplay

static void submitWord()
	submit currently selected word for checking and scoring
static void updateTextAssets()
	update score and current word text
static void reset()
	reset the gameboard, giving all new letters

static void exitGame()
	sets the running variable to false, giving api the signal to end the game
*/

#ifndef WORDPLAYCONTROL_H
#define WORDPLAYCONTROL_H
#include "tile.h"
#include "board.h"
#include "dictionary.h"
#include "../api_code/GameFramework.h"
#include "../api_code/GFSprite.h"
#include <sstream>

enum GameStatus {CHOOSE_LEVEL, INSTRUCTIONS_1, INSTRUCTIONS_2, IN_GAME, DIALOGUE_EXIT, DIALOGUE_RESET};
static GameStatus currentState;
static GFSprite * background;
static Dictionary * userDictionary;
static Board * gameBoard;
static GFSprite * overlay;
static GFText * currentWord;
static GFText * currentScore;

static int score;

static bool running;

class WordplayControl{

	public:
		static void masterClickHandler(int, int, int, int);
		static bool returnRunning();
		static void start();

	private:
		static void introClickHandler(int x, int y);
		static void instructionsClickHandler(int x, int y, int instructionsPage);
		static void inGameClickHandler(int x, int y);
		static void gameboardClickHandler(int x, int y);
		static void dialogueClickHandler(int x, int y, void (*yesFunction)(), void (*noFunction)());

		static void showInstructions(int gameLevel, int page);
		static void beginGame();
		
		static void dialogueBox(string name);
		static void endDialogue();
		
		static void submitWord();
		static void updateTextAssets();
		static void reset();

		static void exitGame();
};



#endif