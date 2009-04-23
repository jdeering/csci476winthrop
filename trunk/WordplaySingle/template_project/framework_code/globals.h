//globals
#ifndef GLOBALS_H
#define GLOBALS_H

#define ALLEGRO_AND_MFC
#define ALLEGRO_NO_MAGIC_MAIN

// Allegro and Speech API
#include "../allegro_headers/allegro.h"
#include "../allegro_headers/winalleg.h"
#include "sapi.h"

// STL paths
#include <vector>
#include <string>
#include <iostream>
#include <string>
#include <map>
#include <sstream>

//#include "Board.h"
//#include "Dictionary.h"
//#include "Tile.h"
//#include "GFSprite.h"
//#include "GFText.h"
//#include "GFAudio.h"
using namespace std;


// The index for the game to launch.
// This should reflect the game's relative
// location to other games in the Games.XML
// file. 0 is the first game.
#define GAMENUM 0


#define MAXSPRITES		500
#define MAXFILES		100
#define MAXGAMES		4
#define XOFFSET			200

// Audio Values
#define PAN 128
#define FREQ 1000
#define MAX_VOLUME 255
#define MIN_VOLUME 0


#endif