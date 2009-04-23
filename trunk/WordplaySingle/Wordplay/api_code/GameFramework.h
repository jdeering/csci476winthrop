/**
 *		@file GameFramework.h
 *		@brief The class used for the YCADC Game Framework Developer API
 */
 
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
	TEXT_SIZE_CHANGE			= 407,
	TEXT_COLOR_CHANGE			= 408,
	TEXT_BGCOLOR_CHANGE			= 409,
	TEXT_READ					= 410,
	
	/* AUDIO OPCODES */
	AUDIO_CREATE				= 501,
	AUDIO_REMOVE				= 502,
	AUDIO_PLAY					= 503,
	AUDIO_SET_LOOP_COUNT		= 504,
	AUDIO_STOP					= 505,

	/* SCORE TO POST */
	POST_SCORE					= 601,
	
	/* MISCELLANEOUS OPCODES */
};

#include "engine.h"
#include "GFSprite.h"
#include "GFText.h"
#include "GFAudio.h"
#include "allegro.h"
#include "winalleg.h"
#include <sstream>

/**
 *		Static class. Acts as the developer API, bridging developer to the framework.
 */
/* STATIC */ class GameFramework
{
	private:
	
		static int const GFW_BUFFER_SIZE = 128;
		static int const INDEX_TABLE_SIZE = 1000;
	
	public:
		
		/** 	@brief Public constructor
		 */
		GameFramework(){ SetNamedPipeHandleState(stdoutFW, PIPE_WAIT, NULL, NULL); }
		~GameFramework(){ CloseHandle(stdinFW); CloseHandle(stdoutFW); }
		
		/** 	@brief Create an instance of the Game Engine
		 *		@param userName 	player username
		 */
		static void CreateEngineInstance(std::string userName){ ENGINE = Framework::Instance(userName); }
		
		/* SCORE */
		static unsigned long long int score;
		static bool pause;
		
		/* SEND A MESSAGE (FROM OTHER CLASSES) */
		static char _msgBuffer[GFW_BUFFER_SIZE];
		
		
		/** 	@brief Send the message stored in _msgBuffer
		 */
		static void sendMessage();
		
		/* SET CALLBACK FUNCTIONS */
		
		/** 	@brief Set the keyboard callback function
		 *		@param f 		callback function (void function, passed key, state)
		 */
		static void kybdFunc(void (*f)(int, int));
		static void kybdMessage(const char *);
		
		/** 	@brief Set the mouse click callback function
		 *		@param f 		callback function (void function passed button, new state, x, y)
		 */
		static void mouseFunc(void (*f)(int, int, int, int));
		static void mouseMessage(const char *);
		
		/** 	@brief Set the mouse click callback function
		 *		@param f 		callback function (void function passed key, new state, GFSprite reference)
		 */
		static void spriteClickFunc(void (*f)(int, int, GFSprite&));
		
		/** 	@brief Set the game callback function
		 *		@param f 		callback function (void function passed flag to denote whether to continue looping)
		 */
		static void gameFunc(bool (*f)());

		/* START LOOP FUNCTION */
		
		/** 	@brief Begin the gameplay loop
		 */
		static void gameLoop();
		
		/* GRAPHICS FUNCTIONS */
		
		/** 	@brief Create a sprite object from an asset name (referencing the asset XML file)
		 *		@param s 		asset name
		 *		@param x 		x-position
		 *		@param y 		y-position
		 *		@param w 		width
		 *		@param h 		height
		 */
		static GFSprite& createSprite(std::string s, int x, int y, int w, int h);
		
		/** 	@brief Create a sprite object from an asset name (referencing the asset XML file)
		 *		@param s 		asset name
		 *		@param x 		x-position
		 *		@param y 		y-position
		 */
		static GFSprite& createSprite(std::string s, int x, int y);
		
		/** 	@brief Destory a GFSprite
		 *		@param s		GFSprite reference to destroy
		 */
		static void removeSprite(GFSprite& s);
		
		/* TEXT FUNCTIONS */
		
		/** 	@brief Create a text object from an asset name (referencing the asset XML file)
		 *		@param s 		asset name
		 *		@param x 		x-position
		 *		@param y 		y-position
		 */
		static GFText& createTextFromAsset(std::string s, int x, int y);
		
		/** 	@brief Create a text object from a string
		 *		@param s 		text contents
		 *		@param x 		x-position
		 *		@param y 		y-position
		 */
		static GFText& createTextFromString(std::string s, int x, int y);
		
		/** 	@brief Destroy a GFText object
		 *		@param t		GFText reference to destroy
		 */
		static void removeText(GFText& t);
		
		/** 	@brief Read a piece of text using TTS
		 *		@param t		Text to be read by the text-to-speech module
		 */
		static void readText(std::string t);
		
		/** 	@brief Set a GFText object's text size
		 *		@param t		GFText
		 *		@param s		new text size
		 */
		static void setTextSize(GFText& t, int s);
		
		/** 	@brief Set a GFText object's text color
		 *		@param t		GFText
		 *		@param r		red channel
		 *		@param g		blue channel
		 *		@param b		green channel
		 */
		static void setTextColor(GFText& t, int r, int g, int b);
		
		/** 	@brief Set a GFText object's background color
		 *		@param t		GFText
		 *		@param r		red channel
		 *		@param g		blue channel
		 *		@param b		green channel
		 */
		static void setTextBGColor(GFText& t, int r, int g, int b);
		
		/* AUDIO FUNCTIONS */
		
		/** 	@brief Create an audio object from an asset name (referencing the asset XML file)
		 *		@param s 		asset name
		 */
		static GFAudio& createAudio(std::string s);
		
		/** 	@brief Destroy a GFAudio object
		 *		@param a 		GFAudio object to destroy
		 */
		static void removeAudio(GFAudio& a);

		/* SEND SCORE */
		/** 	@brief Post the score back to the Framework engine.
		 */
		static void postScore();

		/* MOUSE POSITION */
		
		/** 	@brief Mouse position properties
		 */
		static int mouseX, mouseY;
		
		static Framework *ENGINE;
		
	private:
		
		/* GETTER FUNCTIONS */
		static GFSprite& getSprite(int r);
		static GFText& getTextObj(int r);
		static GFAudio& getAudioObj(int r);
	
		/* COMMUNICATION DETAILS */
		static HANDLE stdinFW, stdoutFW, stderrFW;
		
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

