#include <string>
#include <list>

#include "GFSprite.h"
#include "GFText.h"
#include "GFAudio.h"

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
		void gameFunc(void (*f)());

		/* START LOOP FUNCTION */
		void gameLoop();
		
		/* GRAPHICS FUNCTIONS */
		GFSprite& createSprite(std::string, int, int, int, int);
		
		/* TEXT FUNCTIONS */
		GFText& createTextFromAsset(std::string, int, int, int);
		GFText& createTextFromString(std::string, int, int, int);
		
		/* AUDIO FUNCTIONS */
		GFAudio& createAudio(std::string, int, int);
		
	protected:
		/* PROTECTED CONSTRUCTORS */
		GameFramework();
		
	private:
		/* OBJECT LIST SIZES */
		static int const GFS_MAX;
		static int const GFT_MAX;
		static int const GFA_MAX;

		/* OBJECT COUNTS AND INDICES */
		int gfs_count, gfsi;
		int gft_count, gfti;
		int gfa_count, gfai;

		/* FUNCTION POINTERS */
		void (*cb_KH)(int, int, int, int);	// CALLBACK - KYBD
		void (*cb_MH)(int, int, int, int);	// CALLBACK - MOUSE
		void (*cb_GL)();			// GAME LOOP

		/* OBJECT LISTS (FOR DESTRUCTION) */
		std::list<GFSprite> 	_gfs;
		std::list<GFText> 	_gft;
		std::list<GFAudio> 	_gfa;
};

/* DEVELOPERS SHOULD USE THIS AS THEIR DATATYPE */
typedef GameFramework& GFInstance;
