//globals
//#include "../../APIFramework/GameFramework.h"
#ifndef GLOBALS_H
#define GLOBALS_H

#include "../classes/Board.h"
#include "../classes/Dictionary.h"
#include "../classes/Tile.h"
#include <vector>
#include <string>
using namespace std;

Board * gameBoard;
Dictionary * userDictionary;
enum GameStatus {CHOOSE_LEVEL, INSTRUCTIONS_1, INSTRUCTIONS_2, IN_GAME, DIALOGUE_EXIT, DIALOGUE_RESET};
GameStatus currentState = CHOOSE_LEVEL;
vector <GFSprite> overlays;
GFText * gScore;
int score;
GFText * currentWord;
bool gameRunning = true;
GFSprite * background;

void masterClickHandler(int, int, int, int);
void introClickHandler(int x, int y);
void instructionsClickHandler(int x, int y, int instructionsPage);
void inGameClickHandler(int x, int y);
void dialogueClickHandler(int x, int y, void * yesFunction, void * noFunction);
void gameboardClickHandler(int x, int y);


void dialogueBox(string name);
void showInstructions(int gameLevel, int page);
void removeAllButGameboard();
void endDialogue();
void updateScore();
void updateCurrentWord();

void constructBoard(int level);
void makeDictionary();
void beginGame();
void exitGame();
void resetBoard();
void submitWord();

#endif