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
};

#include "GFSprite.h"
#include "GFText.h"
#include "GFAudio.h"
#include "windows.h"

class /*SINGLETON*/ GameFramework
{
	public:
		
		/* SCORE */
		unsigned long long int score;
		
		/* PUBLIC DESTRUCTOR */
		~GameFramework();

		/* SINGLETON INSTANCE METHOD */
		static GameFramework& Instance();
		
		/* SEND A MESSAGE (FROM OTHER CLASSES) */
		void sendMessage(char*);
		
		/* SET CALLBACK FUNCTIONS */
		// f is function that takes (int -> key, int -> new state)
		void kybdFunc(void (*f)(int, int));
		
		// f is function that takes (int -> button, int -> new state, int -> x, int -> y)
		void mouseFunc(void (*f)(int, int, int, int));
		
		// f is function that takes (int -> key, int -> new state, GFSprite& -> sprite clicked)
		void spriteClickFunc(void (*f)(int, int, GFSprite&));
		
		// f is function that returns bool (true -> continue looping)
		void gameFunc(bool (*f)());

		/* START LOOP FUNCTION */
		void gameLoop();
		
		/* GRAPHICS FUNCTIONS */
		
		// string -> asset name, int -> x, int -> y, int -> width, int -> height
		GFSprite& createSprite(std::string, int, int, int, int);
		GFSprite& createSprite(std::string, int, int);
		void removeSprite(GFSprite&);
		
		/* TEXT FUNCTIONS */
		// string -> asset name, 
		GFText& createTextFromAsset(std::string, int, int, int);
		GFText& createTextFromString(std::string, int, int, int);
		void removeText(GFText&);
		
		/* AUDIO FUNCTIONS */
		GFAudio& createAudio(std::string);
		void removeAudio(GFAudio&);

		/* MOUSE POSITION */
		int mouseX, mouseY;
		
		/* GETTER FUNCTIONS */
		GFSprite& getSprite(int r);
		GFText& getTextObj(int r);
		GFAudio& getAudioObj(int r);
		
	protected:
	
		/* PROTECTED CONSTRUCTORS */
		GameFramework();
		
	private:
	
		static int const GFW_BUFFER_SIZE = 512;
		static int const INDEX_TABLE_SIZE = 1000;
	
		/* COMMUNICATION DETAILS */
		//HANDLE stdinFW, stdoutFW;
		char _msgBuffer[GFW_BUFFER_SIZE];
		
		/* CLEANUP METHODS */
		void _clrBuffer();
		void _getMessages();

		/* OBJECT LIST SIZES */
		static int const GFS_MAX, GFSL, GFSU;
		static int const GFT_MAX, GFTL, GFTU;
		static int const GFA_MAX, GFAL, GFAU;

		/* OBJECT COUNTS AND INDICES */
		int gfs_count, gfsi;
		int gft_count, gfti;
		int gfa_count, gfai;

		/* INDEX TABLE */
		int _index_table[INDEX_TABLE_SIZE];
		static int const INDEX_TAKEN;
		static int const INDEX_AVAIL;

		/* FUNCTION POINTERS */
		void (*cb_KH)(int, int);		// CALLBACK - KYBD
		void (*cb_MH)(int, int, int, int);	// CALLBACK - MOUSE
		void (*cb_SH)(int, int, GFSprite&);	// CALLBACK - SPRITE CLICK
		bool (*cb_GL)();			// GAME LOOP

		/* OBJECT LISTS (FOR DESTRUCTION) */
		std::list<GFSprite> 	_gfs;
		std::list<GFText> 	_gft;
		std::list<GFAudio> 	_gfa;
};

