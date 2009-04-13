//globals
#ifndef GLOBALS_H
#define GLOBALS_H

#define ALLEGRO_AND_MFC
#define ALLEGRO_NO_MAGIC_MAIN

// Allegro and Speech API
#include "Allegro Headers/allegro.h"
#include "Allegro Headers/winalleg.h"
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