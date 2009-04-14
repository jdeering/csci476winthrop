#ifndef WORDPLAYCONTROL_H
#define WORDPLAYCONTROL_H
#include "tile.h"
#include "board.h"
#include "dictionary.h"
#include "GameFramework.h"
#include "GFSprite.h"
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
		static void updateScoreText();
		static void reset();

		static void exitGame();
};



#endif