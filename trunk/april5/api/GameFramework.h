#pragma once
#include <string>
#include <list>

enum PROTOCOL_OPCODES
{
	/* MOUSE OPCODES */
	MOUSE_LOCATION_UPDATE 		= 101,
	MOUSE_STATE_CHANGE			= 102,
	MOUSE_SPRITE_CLICK			= 103,
	
	/* KEYBOARD OPCODES */
	KEY_STATE_CHANGE			= 201,
	
	/* SPRITE OPCODES */
	SPRITE_CREATE				= 301,
	SPRITE_CREATE_FROM_ASSET	= 302,
	SPRITE_REMOVE				= 303,
	SPRITE_VISIBILITY_CHANGE	= 304,
	SPRITE_SET_SIZE				= 305,
	SPRITE_SET_LOCATION			= 306,
	SPRITE_SET_FRAME_DELAY		= 307,
	SPRITE_SET_ANIMATION		= 308,
	SPRITE_SET_FRAME			= 309,
	SPRITE_MOVE_TO				= 310,
	SPRITE_CHANGE_BITMAP		= 311,
	
	/* TEXT OPCODES */
	TEXT_CREATE_FROM_ASSET		= 401,
	TEXT_CREATE_FROM_STRING		= 402,
	TEXT_REMOVE					= 403,
	TEXT_CHANGE_CONTENT			= 404,
	TEXT_CHANGE_LOCATION		= 405,
	TEXT_VISIBILITY_CHANGE		= 406,
	
	/* AUDIO OPCODES */
	AUDIO_CREATE				= 501,
	AUDIO_REMOVE				= 502,
	AUDIO_PLAY					= 503,
	AUDIO_SET_LOOP_COUNT		= 504,
	AUDIO_STOP					= 505,
	
	/* MISCELLANEOUS OPCODES */
};

#include "GFSprite.h"
#include "GFText.h"
#include "GFAudio.h"
#include "windows.h"
#include <sstream>

/* STATIC */ class GameFramework
{
	private:
	
		static int const GFW_BUFFER_SIZE = 512;
		static int const INDEX_TABLE_SIZE = 1000;
	
	public:
		
		/* SCORE */
		static unsigned long long int score;
		
		/* SEND A MESSAGE (FROM OTHER CLASSES) */
		static char _msgBuffer[GFW_BUFFER_SIZE];
		static void sendMessage();
		
		/* SET CALLBACK FUNCTIONS */
		// f is function that takes (int -> key, int -> new state)
		static void kybdFunc(void (*f)(int, int));
		
		// f is function that takes (int -> button, int -> new state, int -> x, int -> y)
		static void mouseFunc(void (*f)(int, int, int, int));
		
		// f is function that takes (int -> key, int -> new state, GFSprite& -> sprite clicked)
		static void spriteClickFunc(void (*f)(int, int, GFSprite&));
		
		// f is function that returns bool (true -> continue looping)
		static void gameFunc(bool (*f)());

		/* START LOOP FUNCTION */
		static void gameLoop();
		
		/* GRAPHICS FUNCTIONS */
		
		// string -> asset name, int -> x, int -> y, int -> width, int -> height
		static GFSprite& createSprite(std::string, int, int, int, int);
		static GFSprite& createSprite(std::string, int, int);
		static void removeSprite(GFSprite&);
		
		/* TEXT FUNCTIONS */
		// string -> asset name, 
		static GFText& createTextFromAsset(std::string, int, int, int);
		static GFText& createTextFromString(std::string, int, int, int);
		static void removeText(GFText&);
		
		/* AUDIO FUNCTIONS */
		static GFAudio& createAudio(std::string);
		static void removeAudio(GFAudio&);

		/* MOUSE POSITION */
		static int mouseX, mouseY;
		
		/* GETTER FUNCTIONS */
		static GFSprite& getSprite(int r);
		static GFText& getTextObj(int r);
		static GFAudio& getAudioObj(int r);
		
	private:
	
		/* COMMUNICATION DETAILS */
		static HANDLE stdinFW, stdoutFW;
		
		static void _getMessages();
		static void _parseMessage(std::stringstream&);
		
		/* CLEANUP METHODS */
		static void _clrBuffer();

		/* OBJECT LIST SIZES */
		static int const GFS_MAX, GFSL, GFSU;
		static int const GFT_MAX, GFTL, GFTU;
		static int const GFA_MAX, GFAL, GFAU;

		/* OBJECT COUNTS AND INDICES */
		static int gfs_count, gfsi;
		static int gft_count, gfti;
		static int gfa_count, gfai;

		/* INDEX TABLE */
		static int _index_table[INDEX_TABLE_SIZE];
		static int const INDEX_TAKEN;
		static int const INDEX_AVAIL;

		/* FUNCTION POINTERS */
		static void (*cb_KH)(int, int);				// CALLBACK - KYBD
		static void (*cb_MH)(int, int, int, int);	// CALLBACK - MOUSE
		static void (*cb_SH)(int, int, GFSprite&);	// CALLBACK - SPRITE CLICK
		static bool (*cb_GL)();						// GAME LOOP

		/* OBJECT LISTS (FOR DESTRUCTION) */
		static std::list<GFSprite> 	_gfs;
		static std::list<GFText> 	_gft;
		static std::list<GFAudio> 	_gfa;
};

