#include <string>
#include <list>

#define INDEX_TABLE_SIZE 1000

#include "GFSprite.h"
#include "GFText.h"
#include "GFAudio.h"

//#include <winalleg.h>

#ifndef GFW_BUFFER_SIZE
	#define GFW_BUFFER_SIZE 512
#endif

class /*SINGLETON*/ GameFramework
{
	public:
		/* PUBLIC DESTRUCTOR */
		~GameFramework();

		/* SINGLETON INSTANCE METHOD */
		static GameFramework& Instance();
		
		/* SET CALLBACK FUNCTIONS */
		void kybdFunc(void (*f)(int, int, int, int));
		void mouseFunc(void (*f)(int, int, int, int));
		void gameFunc(bool (*f)());

		/* START LOOP FUNCTION */
		void gameLoop();
		
		/* GRAPHICS FUNCTIONS */
		GFSprite& createSprite(std::string, int, int, int, int);
		void removeSprite(GFSprite&);
		
		/* TEXT FUNCTIONS */
		GFText& createTextFromAsset(std::string, int, int, int);
		GFText& createTextFromString(std::string, int, int, int);
		void removeText(GFText&);
		
		/* AUDIO FUNCTIONS */
		GFAudio& createAudio(std::string);
		void removeAudio(GFAudio&);
		
	protected:
		/* PROTECTED CONSTRUCTORS */
		GameFramework();
		
	private:
		/* COMMUNICATION DETAILS */
		//HANDLE stdinFW, stdoutFW;
		char _msgBuffer[GFW_BUFFER_SIZE];
		void _clrBuffer();

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
		void (*cb_KH)(int, int, int, int);	// CALLBACK - KYBD
		void (*cb_MH)(int, int, int, int);	// CALLBACK - MOUSE
		bool (*cb_GL)();			// GAME LOOP

		/* OBJECT LISTS (FOR DESTRUCTION) */
		std::list<GFSprite> 	_gfs;
		std::list<GFText> 	_gft;
		std::list<GFAudio> 	_gfa;
};

