/*
Lauren Cairco
13 April 2009
CSCI 476 Project

Templatecontrol.h


GLOBAL VARIABLES
static bool running
	holds whether the game is running or not
static int score
	holds game score (not the framework variable)


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
static void exitGame()
	sets the running variable to false, giving api the signal to end the game
*/

#ifndef TEMPLATECONTROL_H
#define TEMPLATECONTROL_H

#include "../api_code/GameFramework.h"
#include "../api_code/GFSprite.h"
#include <sstream>


static int score;
static bool running;

class TemplateControl{

	public:
		static void masterClickHandler(int, int, int, int);
		static bool returnRunning();
		static void start();

	private:
		static void exitGame();
};



#endif