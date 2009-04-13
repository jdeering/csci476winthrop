#pragma once
#include <string>

#include "GFObject.h"
class GFAudio : public GFObject
{
	/* SO THAT THE FRAMEWORK CAN ACCESS PROTECTED MEMBERS */
	friend class GameFramework;

	public:
		/* PUBLIC DESTRUCTOR */
		~GFAudio();
		
		/* NULL OBJECT */
		static const GFAudio null;

		/* CONSTANTS FOR AUDIO PLAYBACK */
		static const int STOP = 0;
		static const int PLAY = 1;

		/* PLAYBACK FUNCTIONS */
		void play();
		void stop();
		void setLoopCount(int);

		/* PRINT FUNCTION (FOR DEBUG) */
		friend std::ostream& operator<<(std::ostream&, GFAudio&);

	protected:
		/* PROTECTED CONSTRUCTOR */
		GFAudio(int);
};
