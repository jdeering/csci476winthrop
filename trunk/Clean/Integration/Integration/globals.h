#ifndef _GLOBALS_H
#define _GLOBALS_H
#define ALLEGRO_AND_MFC
#define ALLEGRO_NO_MAGIC_MAIN

#include "allegro.h"
#include "winalleg.h"
#include "sapi.h"
#include <iostream>
#include <string>
#include <map>
#include <sstream>

#define MAXSPRITES		500
#define MAXFILES		100
#define MAXGAMES		4
#define XOFFSET			200
#define DEBUG			0




	/* MOUSE OPCODES */
#define	MOUSE_LOCATION_UPDATE 		 101
#define	MOUSE_STATE_CHANGE			 102
#define	MOUSE_SPRITE_CLICK			 103
	
	/* KEYBOARD OPCODES */
#define	KEY_STATE_CHANGE			 201
	
	/* SPRITE OPCODES */
#define	SPRITE_CREATE				 301
#define	SPRITE_CREATE_FROM_ASSET	 302
#define	SPRITE_REMOVE				 303
#define	SPRITE_VISIBILITY_CHANGE	 304
#define	SPRITE_SET_SIZE				 305
#define	SPRITE_SET_LOCATION			 306
#define	SPRITE_SET_FRAME_DELAY		 307
#define	SPRITE_SET_ANIMATION		 308
#define	SPRITE_SET_FRAME			 309
#define	SPRITE_MOVE_TO				 310
#define SPRITE_CHANGE_BITMAP		 311
	
	/* TEXT OPCODES */
#define	TEXT_CREATE_FROM_ASSET		 401
#define	TEXT_CREATE_FROM_STRING		 402
#define	TEXT_REMOVE					 403
#define	TEXT_CHANGE_CONTENT			 404
#define	TEXT_CHANGE_LOCATION		 405
#define	TEXT_VISIBILITY_CHANGE		 406
	
	/* AUDIO OPCODES */
#define	AUDIO_CREATE				 501
#define	AUDIO_REMOVE				 502
#define	AUDIO_PLAY					 503
#define	AUDIO_SET_LOOP_COUNT		 504
#define	AUDIO_STOP					 505

#define SCORE						 601

#endif